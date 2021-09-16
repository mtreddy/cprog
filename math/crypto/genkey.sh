#!/bin/sh
# Generate key
openssl ecparam -genkey -name sect283r1 -noout -out private.pem -param_enc explicit
openssl ec -in private.pem -pubout -out public.pem 
