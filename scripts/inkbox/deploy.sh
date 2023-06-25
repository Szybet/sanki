#!/bin/bash

cd ../../

cp build/kobo/sanki inkbox_userapp/sanki/app-bin/sanki.bin

# Very important
rm -f inkbox_userapp/sanki.isa.dgst
rm -f inkbox_userapp/sanki.isa

mksquashfs inkbox_userapp/sanki/* inkbox_userapp/sanki.isa

# Yes, here are my private keys. Is providing this info a security threat? no.
openssl dgst -sha256 -sign /home/szybet/inkbox-keys/userapps.pem -out inkbox_userapp/sanki.isa.dgst inkbox_userapp/sanki.isa

servername="root@10.42.0.28"
passwd="root"

sshpass -p $passwd ssh $servername "bash -c \"ifsctl mnt rootfs rw\""
# sshpass -p $passwd ssh $servername "bash -c \"rm -r /data/onboard/.apps/sanki\""
sshpass -p $passwd ssh $servername "bash -c \"mkdir /data/onboard/.apps/sanki\""
sshpass -p $passwd ssh $servername "bash -c \"rm  /data/onboard/.apps/sanki/sanki.isa\""
sshpass -p $passwd ssh $servername "bash -c \"rm  /data/onboard/.apps/sanki/sanki.isa.dgst\""
sshpass -p $passwd ssh $servername "bash -c \"rm  /data/onboard/.apps/sanki/app.json\""


sshpass -p $passwd scp inkbox_userapp/app.json $servername:/data/onboard/.apps/sanki/
sshpass -p $passwd scp inkbox_userapp/sanki.isa.dgst $servername:/data/onboard/.apps/sanki/
sshpass -p $passwd scp inkbox_userapp/sanki.isa $servername:/data/onboard/.apps/sanki/

sshpass -p $passwd ssh $servername "bash -c \"touch /kobo/tmp/rescan_userapps\""

sshpass -p $passwd ssh $servername "bash -c \"sync\""

sshpass -p $passwd ssh $servername "bash -c \"killall -9 sanki-debug.sh\"" || EXIT_CODE=0
sshpass -p $passwd ssh $servername "bash -c \"killall -9 sanki.sh\"" || EXIT_CODE=0

sshpass -p $passwd ssh $servername "bash -c \"rc-service inkbox_gui restart\"" # to get logs
# sshpass -p $passwd ssh $servername "bash -c \"rc-service gui_apps restart\""

# To update main json
# sshpass -p $passwd ssh $servername "bash -c \"touch /kobo/tmp/rescan_userapps\"" # This gets deleted by service restart
#sshpass -p $passwd ssh $servername "bash -c \"killall inkbox-bin\""
#sleep 10
