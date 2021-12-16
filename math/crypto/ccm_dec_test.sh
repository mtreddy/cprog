#!/bin/sh
openssl_path="/User_data/home/tmarri/src/crypto/openssl/compute8/openssl-1.1.1k/"
export LD_LIBRARY_PATH=$openssl_path
N=2
counter=0
tlen_inp=4
aad="8e997d733ee29aa2904796985e909512"
iv="dd751f9b5784280bf0266ab3b256b370"
skey="9096a9c32de9b3b3e910e4ede0c063b0"
tlen="4"
ctext="93993b37df814b70c01373612f8bed27c6d90555"
echo "AAD   :$aad"
echo "iv    :$iv"
echo "skey  :$skey"
echo "tlen  :$tlen"
echo "ctext :$ctext"
while [ $counter -le $N ]
do
	res=$(./ccm_dec $skey $aad $iv $ctext $tlen)
	echo " $counter "
	echo $res
	counter=$((counter+1))
done
