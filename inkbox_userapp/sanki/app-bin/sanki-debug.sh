#!/system-bin/sh

env -i DEVICE="${DEVICE}" DEVICE_CODENAME="${DEVICE_CODENAME}" QT_FONT_DPI=${QT_FONT_DPI} PATH="/app-bin:/system-bin" LD_LIBRARY_PATH="/system-lib/lib:/system-lib/qt/lib:/app-lib" QT_QPA_PLATFORM="kobo" DEBUG="true" LC_ALL="en_US" /system-lib/lib/ld-linux-armhf.so.3 /app-bin/sanki.bin
