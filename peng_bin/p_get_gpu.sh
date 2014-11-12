#!/bin/bash
# get the gpu directory from 172.23.26.41:/home/pengpengxp/Ac/test/gpu
cd /home/pengpengxp/workshop/
if [ -d "gpu" ]
then
    echo "YES,I'll delete ~/gpu and copy it from 172.23.26.41"
    rm -rfv gpu
    scp -r root@172.23.26.41:/home/pengpengxp/Ac/test/gpu ./
else
    echo "NO,I'll copy it from 172.23.26.41"
    scp -r root@172.23.26.41:/home/pengpengxp/Ac/test/gpu ./
fi

exit 0
