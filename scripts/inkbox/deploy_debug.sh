#!/bin/bash

cd ../../

servername="root@10.42.0.28"
passwd="root"


sshpass -p $passwd ssh $servername "bash -c \"killall -9 sanki inkbox inkbox-bin\""
sshpass -p $passwd ssh $servername "bash -c \"killall -9 sanki inkbox inkbox-bin\""

sshpass -p $passwd ssh $servername "bash -c \"rm /kobo/sanki\""
sshpass -p $passwd scp build/ereader/sanki $servername:/kobo/
sshpass -p $passwd ssh $servername "bash -c \"/kobo/launch_app.sh\""
