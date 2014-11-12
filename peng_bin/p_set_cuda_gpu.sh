#!/bin/bash
# set the gpu directory to 172.23.26.41:/home/pengpengxp/Ac/test/gpu
cd /home/pengpengxp/workshop/

if [ -d "gpu" ]
then
    echo "YES,I'll delete the remote one"
    ssh root@172.23.26.41 rm -rfv /home/pengpengxp/Ac/test/gpu
    # sleep 1
    echo "copy it to 172.23.26.41"
    scp -r ./gpu root@172.23.26.41:/home/pengpengxp/Ac/test/
else
    echo "no gpu directory,nothing need to be done"
    exit -1
fi

exit 0
