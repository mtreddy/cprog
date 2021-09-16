#!/bin/sh
export LD_LIBRARY_PATH="/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/"
openssl="/User_data/home/tmarri/src/crypto/openssl/openssl-1.1.1k/apps/openssl"

if [ $# -ne 1 ]
then
	echo "Usage: ./generateTestVector.sh <Payload to sign>"
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
#openssl ecparam -genkey -name sect283r1 -noout -out private.pem -param_enc explicit

# Sign payload
## Verify sign
#sign=$(openssl dgst -sha3-256 -hex -sign private.pem $payload)
#hsign=$(echo $sign | awk '{print $31}') 
#echo $hsign > hsign.hex
#cat hsign.hex |  xxd -r -p  > hsign.bin
openssl dgst -sha3-256 -verify public.pem  -signature hsign.bin  $payload
