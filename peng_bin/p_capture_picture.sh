#!/bin/bash

FILEDIR="/tmp/screenshot";

if [ -e $FILEDIR ] 
then
    echo "yes"
else
    echo "no"
    mkdir $FILEDIR
fi

import -frame -quality 100 ${FILEDIR}/`date +%Y%m%d_%H%M%S`.png 2>/dev/null

exit 0
