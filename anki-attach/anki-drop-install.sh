#!/bin/bash

cargo install ripdrag
cargo install s2png

mkdir -p ~/.local/share/applications/
mkdir -p ~/.local/bin/

cp anki-drop.desktop ~/.local/share/applications/
cp anki-drop.sh ~/.local/bin/

kbuildsycoca5 --noincremental || true
update-desktop-database || true
