#!/system-bin/sh

# No env -i please...
DEVICE="${DEVICE}" DEVICE_CODENAME="${DEVICE_CODENAME}" QT_FONT_DPI=${QT_FONT_DPI} PATH="/app-bin:/system-bin" LD_LIBRARY_PATH="/system-lib/lib:/system-lib/qt/lib:/app-lib" QT_QPA_PLATFORM="kobo" LC_ALL="en_US" QT_PLUGIN_PATH="/system-lib/qt/plugins/" XDG_CONFIG_HOME="/app-data/" XDG_RUNTIME_DIR="/app-data/" /system-lib/lib/ld-linux-armhf.so.3 /app-bin/sanki.bin
