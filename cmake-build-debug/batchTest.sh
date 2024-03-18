#!/usr/bin/env bash

mkdir test/output

echo  "---------------------------------"
for file in test/*.cmm
do
    echo "Testing $file"
    ./Lab1 $file > "test/output/${file#test/}.pst"
    echo "---------------------------------"
done