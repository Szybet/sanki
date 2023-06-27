# sanki
**s**mall [**anki**](https://apps.ankiweb.net) app rewritten for e-readers, with focus on [InkBox](https://github.com/Kobo-InkBox/inkbox) support

### 0.2 version demo:
https://github.com/Szybet/sanki/raw/master/sanki-demo.mkv

### Supported, tested devices:
- Kobo nia

Should work on all devices, if not, please export debug info in device settings and send me it.

### Sync
To sync sanki with anki ( On Linux host ):
1. Setup anki connect on anki
2. Install rust ( The programming language )
3. Clone the repo, enter sanki-sync repo
4. Run `cargo run --release -- --help`
5. Adjust your command line options, then run the server, wait for it to finish getting all the decks
6. On the ereader, input your host IP address and port like that: <ip_address>:<port> for example 192.168.1.1:8766
7. Sync :)

### Installation
- For Nickel, just extract the zip to the main folder when connecting via usb - You also need Nickel Menu and Kfmon installed
- For InkBox, extract it to `.apps` folder

### Contribute
Everything really is welcome. 

### Building
Instructions can be found [here](https://github.com/Szybet/kobo-nia-audio/tree/main/apps-on-kobo)

### Thanks to
- NiLuJe for providing the toolchain for kobo devices, and helping with some bugs
- tux-linux for developing inkbox and helping with qt magic
- Rain92 for developing the qt5-kobo-platform-plugin

### Donations
If you want to support the project, or request a feature I'm not interested in implementing, please contact ;)
