#!/bin/bash

N=50
counter=0
while [ $counter -le $N ]
do
    rm private.pem
    rm public.pem
    rm hsign.hex
    rm hsign.bin
    rm payload.txt
    sync
    echo vector=$counter
    head -c 128 </dev/urandom >payload.txt
    ((counter++))
    ./genkey.sh
    #sleep 1
    sync
    ./sign.sh payload.txt
    sync
    echo -e "\n"
    ./verify.sh payload.txt
    echo -e "\n\n"
done
