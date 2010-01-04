#!/bin/sh

for i in xdr/*xdr;
do
    echo "Generating `basename $i xdr`h"
    xdrgen --directives=none $i include/ipc_bridge/msgs/`basename $i xdr`h
done