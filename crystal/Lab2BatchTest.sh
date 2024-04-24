#!/usr/bin/env bash

if [ ! -f Lab2 ]; then
    echo "Lab2 not found, please compile it first"
    exit 1
fi

if [ ! -d testLab2 ]; then
    echo "testLab2 directory not found"
    exit 1
fi

if [ ! -d testLab2/output ]; then
    mkdir testLab2/output
fi

echo  "---------------------------------"
for file in testLab2/*.cmm
do
    echo "Testing $file"
    ./Lab2 $file > "testLab2/output/${file#testLab2/}.pst"
    echo "---------------------------------"
done