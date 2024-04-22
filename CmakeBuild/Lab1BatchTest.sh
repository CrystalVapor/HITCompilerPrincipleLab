#!/usr/bin/env bash

if [ ! -f Lab1 ]; then
    echo "Lab1 not found, please compile it first"
    exit 1
fi

if [ ! -d testLab1 ]; then
    echo "test directory not found"
    exit 1
fi

if [ ! -d testLab1/output ]; then
    mkdir testLab1/output
fi

echo  "---------------------------------"
for file in testLab1/*.cmm
do
    echo "Testing $file"
    ./Lab1 $file > "testLab1/output/${file#testLab1/}.pst"
    echo "---------------------------------"
done