#[macro_use]
extern crate log;

use std::fs::File;
use std::{io::Write};
use std::{thread};

use axum::{
    body::Body,
    extract::State,
    handler::HandlerWithoutStateExt,
    http::{Request, StatusCode},
    middleware::map_request_with_state,
    routing::get,
    Router,
};
use serde::{Deserialize, Serialize};
use std::net::SocketAddr;
use tower::ServiceExt;
use tower_http::{
    services::{ServeDir, ServeFile},
    trace::TraceLayer,
};

use clap::Parser;
use std::path::PathBuf;

use std::sync::Arc;
use tokio::sync::Mutex;
use tokio::time;

#[derive(Parser, Debug)]
#[command(author, version, about)]
struct Args {
    #[arg(short, long, default_value_t = 8766)]
    port: u16,
    #[arg(short, long, default_value_t = String::from("decks"))]
    target_directory: String,
    #[arg(short, long, default_value_t = true)]
    omit_default_deck: bool,
}

#[derive(Clone)]
struct AppState {}

static mut DECK_LIST: Mutex<Vec<String>> = Mutex::const_new(Vec::new());

async fn my_middleware<B>(State(state): State<AppState>, request: Request<B>) -> Request<B> {
    // do something with `state` and `request`...
    let mut locked = unsafe { DECK_LIST.lock().await };

    debug!("Current list: {:?}", locked);

    let mut name = request.uri().to_string();
    name.remove(0);

    info!("Requested: {:?}", name);

    let index = locked.iter().position(|r| r == &name);
    if index.is_some() {
        let index_some = index.unwrap();
        locked.remove(index_some);
    } else {
        error!("Requested a file that was not expected");
    }

    request
}

#[derive(Serialize, Deserialize)]
struct AnkiRequest {
    action: String,
    version: i32,
}

#[derive(Serialize, Deserialize)]
struct AnkiParams {
    deck: String,
    path: String,
}

#[derive(Serialize, Deserialize)]
struct AnkiDeckRequest {
    action: String,
    version: i32,
    params: AnkiParams,
}

#[derive(Serialize, Deserialize)]
struct AnkiDeckResult {
    result: Vec<String>,
    error: Option<String>,
}

#[tokio::main]
async fn main() {
    env_logger::init_from_env(
        env_logger::Env::default().filter_or(env_logger::DEFAULT_FILTER_ENV, "info"),
    );
    info!("Starting");

    let args = Args::parse();

    let client = reqwest::Client::new();

    let params_sync: AnkiRequest = AnkiRequest {
        action: String::from("deckNames"),
        version: 6,
    };
    
    client
        .post("http://127.0.0.1:8765")
        .json(&params_sync)
        .send()
        .await
        .expect("Failed to connect to anki connect")
        .text()
        .await
        .unwrap();

    let params: AnkiRequest = AnkiRequest {
        action: String::from("deckNames"),
        version: 6,
    };

    let response_decks = client
        .post("http://127.0.0.1:8765")
        .json(&params)
        .send()
        .await
        .expect("Failed to connect to anki connect")
        .text()
        .await
        .unwrap();

    debug!("Received decks: {}", response_decks);

    let mut decks: AnkiDeckResult = serde_json::from_str(&response_decks).unwrap();

    if args.omit_default_deck {
        decks
            .result
            .remove(decks.result.iter().position(|r| r == "Default").unwrap());
    }

    std::fs::create_dir_all(args.target_directory.clone()).unwrap();
    let path_dir = std::fs::canonicalize(PathBuf::from(args.target_directory.clone()))
        .unwrap()
        .to_str()
        .unwrap()
        .to_string();

    info!("Downloading decks to: {:?}", path_dir);

    for deck_name in decks.result.clone() {
        info!("Exporting deck: \"{}\"", deck_name);
        let params_deck: AnkiParams = AnkiParams {
            deck: deck_name.clone(),
            path: format!("{}/{}.apkg", path_dir, deck_name),
        };

        let request: AnkiDeckRequest = AnkiDeckRequest {
            action: String::from("exportPackage"),
            version: 6,
            params: params_deck,
        };

        let export_deck = client
            .post("http://127.0.0.1:8765")
            .json(&request)
            .send()
            .await
            .expect("Failed to connect to anki connect")
            .text()
            .await
            .unwrap();

        debug!("export deck result: {}", export_deck);
    }

    for deck in decks.result.iter_mut() {
        *deck = format!("{}.apkg", deck);
    }

    {
        let mut locked = unsafe { DECK_LIST.lock().await };
        *locked = decks.result.clone();
        locked.push(String::from("index.txt"));
    }

    let mut file = File::create(format!("{}/{}", path_dir, "index.txt")).unwrap();

    file.write_all(decks.result.join("\n").as_bytes()).unwrap();

    info!("Starting download server");

    let target_dir_clone = args.target_directory.clone();
    let server_thread = tokio::spawn(async move {
        let addr = SocketAddr::from(([0, 0, 0, 0], args.port));

        async fn handle_404() -> (StatusCode, &'static str) {
            (StatusCode::NOT_FOUND, "Not found")
        }

        let server_dir =
            ServeDir::new(&target_dir_clone).not_found_service(handle_404.into_service());

        let state = AppState { /* ... */ };

        let app = Router::new()
            .nest_service("", server_dir)
            .route_layer(map_request_with_state(state.clone(), my_middleware));

        axum::Server::bind(&addr)
            .serve(app.layer(TraceLayer::new_for_http()).into_make_service())
            .await
            .unwrap();
    });

    let loop_thread = tokio::spawn(async move {
        loop {
            thread::sleep(time::Duration::from_millis(5000));

            let locked = unsafe { DECK_LIST.lock().await };
            if locked.is_empty() {
                info!("Downloaded all files");
                break;
            }
        }
    });

    loop_thread.await.unwrap();
    server_thread.abort();
    info!("Finished downloading all decks, cleaning and exiting...");
    if !args.target_directory.is_empty() {
        std::fs::remove_dir_all(path_dir);
    }
    
}
