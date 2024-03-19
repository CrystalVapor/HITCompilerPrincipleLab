#!/usr/bin/env bash

if [ ! -f Lab1 ]; then
    echo "Lab1 not found, please compile it first"
    exit 1
fi

if [ ! -d test ]; then
    echo "test directory not found"
    exit 1
fi

if [ ! -d test/output ]; then
    mkdir test/output
fi

echo  "---------------------------------"
for file in test/*.cmm
do
    echo "Testing $file"
    ./Lab1 $file > "test/output/${file#test/}.pst"
    echo "---------------------------------"
done