#!/bin/bash -x

cd ../../

servername="root@10.42.0.28"
port="2222"

sshpass -p "" ssh -p $port $servername "sh -c \"killall -9 koreader.sh\""
sshpass -p "" ssh -p $port $servername "sh -c \"killall -9 reader.lua\""
sshpass -p "" ssh -p $port $servername "sh -c \"killall -9 sanki.bin\""
sshpass -p "" ssh -p $port $servername "sh -c \"killall -9 sanki.sh\""

sshpass -p "" ssh -p $port $servername "sh -c \"rm -rf /mnt/onboard/.adds/sanki.bin\""
sshpass -p "" ssh -p $port $servername "sh -c \"rm -rf /mnt/onboard/.adds/sanki.sh\""
sshpass -p "" ssh -p $port $servername "sh -c \"mkdir -p /mnt/onboard/.adds/sanki/lib/\""

sshpass -p "" scp -P $port build/ereader/sanki $servername:/mnt/onboard/.adds/sanki/sanki.bin
sshpass -p "" scp -P $port nickel_app/sanki/.adds/sanki/sanki.sh $servername:/mnt/onboard/.adds/sanki/sanki.sh

sshpass -p "" scp -P $port libraries/zip_libraries/lib-build/EREADER/libzip.so $servername:/mnt/onboard/.adds/sanki/lib/
sshpass -p "" scp -P $port libraries/ereader/ereaderdev-lib/ereaderdev/build/libereaderdev.so* $servername:/mnt/onboard/.adds/sanki/lib/

sshpass -p "" ssh -p $port $servername "sh -c \"DEBUG=true /mnt/onboard/.adds/sanki/sanki.sh\""
