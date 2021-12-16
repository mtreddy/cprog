#!/bin/sh
openssl_path="/User_data/home/tmarri/src/crypto/openssl/compute8/openssl-1.1.1k/"
export LD_LIBRARY_PATH=$openssl_path
N=5
counter=0

while [ $counter -le $N ]
do
	aad=$(openssl rand -hex 16)
	iv=$(openssl rand -hex 16)
	skey=$(openssl rand -hex  16)
	ptext=$(openssl rand -hex  16)
	echo "$ptext"
	res=$(./ccm $skey $aad $iv $ptext $tlen)
	echo " $counter "
	echo $res
	counter=$((counter+1))
done
