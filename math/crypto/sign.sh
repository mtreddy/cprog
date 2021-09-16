#!/bin/sh
## https://superuser.com/questions/1023167/can-i-extract-r-and-s-from-an-ecdsa-signature-in-bit-form-and-vica-versa
#export LD_LIBRARY_PATH="/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/"
#oopenssl="/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/apps/openssl"
which $oopenssl 

if [ $# -ne 1 ]
then
	echo "Usage: ./sign.sh <Payload to sign>"
	exit 1
fi

payload=$1
if [ ! -f $payload ]
then
	echo "$payload isn't a valid file"
	exit 1
fi

#payload_hex=$(xxd -i -ps -c 1000000 < $payload)
#echo "payload: $payload_hex"

# Generate key
#oopenssl ecparam -genkey -name sect283r1 -noout -out private.pem -param_enc explicit

# Sign payload
#oopenssl dgst -sha3-256 -sign private.pem $payload > signature.bin
#sign=$(oopenssl dgst -sha3-256 -hex -sign private.pem $payload)
#echo "\n ----- \n"
#echo "sign:$sign"
#echo "\n ----- \n"
hash=$($oopenssl dgst -sha3-256  $payload)
## Verify sign
#oopenssl dgst -sha3-256 -verify public.pem  -signature signature.bin  ram-boot.bin
priv_key=$($oopenssl ec -in private.pem -noout -text 2> /dev/null)
pub_key=$(echo $priv_key  | sed 's/Field.*//' | cut -c 144- | sed 's/ //g' | sed 's/://g')
pr_key=$(echo $priv_key  | sed 's/priv*//' | cut -c 23- | cut  -c 1-113 | sed 's/ //g' | sed 's/://g')
pub_key_without_flag=$(echo $pub_key | cut -c 3-)
xcoord=$(echo $pub_key_without_flag | cut -c -72)
ycoord=$(echo $pub_key_without_flag | cut -c 73-)

### debug ign=$(/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/apps/openssl  dgst -sha3-256 -hex -sign private.pem payload.txt)
#$oopenssl dgst -sha3-256 -hex -sign private.pem $payload
sign=$($oopenssl dgst -sha3-256 -hex -sign private.pem $payload)
echo $sign
#hsign=$(echo $sign | awk '{print $51}') 
hsign=$(echo $sign | awk  '{split($0,a, "= ") ; print a[2] }')
#echo "hsign: $hsign"
echo $hsign > hsign.hex
cat hsign.hex |  xxd -r -p  > hsign.bin
fsize=$(stat -c%s "./hsign.bin")
maxsize=70
#if [ $fsize -lt $maxsize ];
#then
#	ls -l hsign.bin
#	sleep 10
#fi
r=$($oopenssl asn1parse -inform DER -in hsign.bin | sed -n 2p | cut -c 50-)
s=$($oopenssl asn1parse -inform DER -in hsign.bin | sed -n 3p | cut -c 50-)


if [ $? -ne 0 ]
then
	sleep 10
fi
#echo "pr: $pr_key"
echo "X-scr: $xcoord"
echo "Y-scr: $ycoord"
echo "r-scr: $r"
echo "s-scr: $s"

t=$r$s

echo "t-scr: $t"
echo  "hash-scr:$hash"
#echo "sign: $sign"
