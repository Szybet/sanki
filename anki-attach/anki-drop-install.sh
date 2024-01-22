#!/bin/bash

cargo install ripdrag
cargo install s2png

cp anki-drop.desktop ~/.local/share/applications/
cp anki-drop.sh ~/.local/bin/

kbuildsycoca5 --noincremental || true
update-desktop-database || true
