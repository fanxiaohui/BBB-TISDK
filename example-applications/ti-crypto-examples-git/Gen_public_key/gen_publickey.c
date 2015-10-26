/*
 * Public key generation demo
 *
 * Public key generation demo program using OpenSSL EVP apis
 *
 * Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include <stdio.h>
#include <stdlib.h>

#include <openssl/pem.h>

EVP_PKEY* ReadPrivKey_FromFile(char* filename, char* pass);

int main(int argc, char **argv)
{
    EVP_PKEY *pkey=NULL;
    FILE  *fppub;
 
    pkey = ReadPrivKey_FromFile("/home/root/privatekey.pem", NULL);
	
    fppub = fopen("/home/root/pubkey.pem", "w");
    PEM_write_PUBKEY(fppub, pkey);  //write public key to file pointer fppub
    PEM_write_PUBKEY(stdout, pkey); //write public key to stdout for output
    	
    EVP_PKEY_free(pkey);
    fclose(fppub);
    return 1;
err:
    return 0;
}

/*
* Read private key from file
* Prviate key file name: privatekey.pem
*/

EVP_PKEY* ReadPrivKey_FromFile(char* filename, char* pass)
{
    int i;
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        	printf ("%s can't be opened. Plese run Certificate Genrataion demo first\n", filename);	
    		return 0;
	}
    EVP_PKEY* key = NULL;
    PEM_read_PrivateKey(fp, &key, NULL, pass); //read into file pionter fp from key structure
    fclose(fp);
    
    return key;
}

