#!/bin/bash

cd ../../

servername="root@10.42.0.28"
passwd="root"


sshpass -p $passwd ssh $servername "bash -c \"killall -9 sanki\""
sshpass -p $passwd ssh $servername "bash -c \"killall -9 sanki\""

sshpass -p $passwd ssh $servername "bash -c \"rm /kobo/sanki\""
sshpass -p $passwd scp build/kobo/sanki $servername:/kobo/
sshpass -p $passwd ssh $servername "bash -c \"chroot /kobo /launch_app.sh\""
