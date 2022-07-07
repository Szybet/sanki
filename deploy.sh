#!/bin/bash

cp sanki inkbox_userapp/sanki/app-bin/sanki.bin

mksquashfs inkbox_userapp/sanki/* inkbox_userapp/sanki.isa

# Yes, here are my private keys and yes im using Syncthing. Is providing this info a security thread? no.
openssl dgst -sha256 -sign ~/Syncthing/inkbox-keys/userapps/private.pem -out inkbox_userapp/sanki.isa.dgst inkbox_userapp/sanki.isa

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

sshpass -p $passwd ssh $servername "bash -c \"echo true > /kobo/tmp/rescan_userapps\""
sshpass -p $passwd ssh $servername "bash -c \"echo true > /tmp/rescan_userapps\"" # not sure

sshpass -p $passwd ssh $servername "bash -c \"sync\""
sshpass -p $passwd ssh $servername "bash -c \"rc-service inkbox_gui restart\""
sshpass -p $passwd ssh $servername "bash -c \"rc-service gui_apps restart\""

