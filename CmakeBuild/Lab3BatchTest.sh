#!/usr/bin/env bash

if [ ! -f Lab3 ]; then
    echo "Lab3 not found, please compile it first"
    exit 1
fi

if [ ! -d testLab3 ]; then
    echo "testLab3 directory not found"
    exit 1
fi

if [ ! -d testLab3/output ]; then
    mkdir testLab3/output
fi

echo  "---------------------------------"
for file in testLab3/*.cmm
do
    echo "Testing $file"
    ./Lab3 $file > "testLab3/output/${file#testLab3/}.pst"
    echo "---------------------------------"
done