#!/bin/bash
# undo can't be used
INSTALLDIR=/usr/local/openkeeper/

if [ "`/usr/bin/id -u`" != "0" ]
then
    echo you must be root!!
    exit 1
fi

echo OK,you are root now

if test -z "`cat Netkeeper.dat`"
then
    echo "you need to put writename in Netkeeper.dat"
    exit 1
fi

echo "make the account"
make


mkdir $INSTALLDIR
cp -rv ./* $INSTALLDIR

ln -sf $INSTALLDIR/ok /usr/bin/ok
ln -sf $INSTALLDIR/ok_9m_loop /usr/bin/ok_9m_loop
ln -sf $INSTALLDIR/ok_ns_loop /usr/bin/ok_ns_loop

echo OK,enjoy

exit 0

