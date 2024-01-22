#!/bin/bash

remove_non_ascii() {
    echo "$1" | iconv -c -t ASCII//TRANSLIT
}

file="$1"

filename=$(basename "$file")
filename_clear=$(remove_non_ascii "$filename")

rm -rf /tmp/anki-drop/
mkdir /tmp/anki-drop/
s2png -o "/tmp/anki-drop/${filename_clear}.png" -b "$filename_clear" -s "$file"
ripdrag -x -a -n -d "/tmp/anki-drop/${filename_clear}.png"
