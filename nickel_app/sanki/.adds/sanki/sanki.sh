#!/bin/sh

# Partially coppied from Plato & Koreader
sync
killall -TERM nickel hindenburg sickel fickel adobehost foxitpdf iink dhcpcd-dbus dhcpcd fmon > /dev/null 2>&1
ORIG_BPP=$(./bin/utils/fbdepth -g)

LD_LIBRARY_PATH="/mnt/onboard/.adds/qt-linux-5.15.2-kobo/lib/:/mnt/onboard/.adds/sanki/lib/:/lib/" QT_QPA_PLATFORM="kobo" LC_ALL="en_US" QT_PLUGIN_PATH="/mnt/onboard/.adds/qt-linux-5.15.2-kobo/plugins/" XDG_CONFIG_HOME="/mnt/onboard/.adds/sanki/" XDG_RUNTIME_DIR="/mnt/onboard/.adds/sanki/" /mnt/onboard/.adds/sanki/sanki.bin

[ "$ORIG_BPP" ] && ./bin/utils/fbdepth -q -d "$ORIG_BPP"
/mnt/onboard/.adds/sanki/nickel.sh
