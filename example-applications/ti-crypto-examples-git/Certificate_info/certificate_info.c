/*
 * Certificate information demo
 *
 * Certificate information demo program
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
#include <openssl/x509.h>
#include <openssl/pem.h>

int main(int argc, char** argv)
{
    int i;
    char *filename = "/home/root/certificate.pem";
    FILE* f = fopen(filename, "r");

    if (f == NULL) {
        	printf ("certificate.pem can't be opened. Please run Certificate Generation demo first\n");
    		return 0;
    }
    else
    {
        X509* x509 = PEM_read_X509(f, NULL, NULL, NULL);
        if (x509 != NULL)
        {

            long pver = X509_get_version(x509);    //get Version information
	    printf("Version: %d(0x%x)\n", pver+1,pver);

	    ASN1_INTEGER *serial = X509_get_serialNumber(x509);   //get Serial Number information
	    long psn = ASN1_INTEGER_get(serial);
	    printf("SerialNumber: %ld\n", psn);

  	    const char* psign = OBJ_nid2ln(OBJ_obj2nid(x509->sig_alg->algorithm));    //get Signature Algorithm information
            printf("Signature Algorithm: %s\n", psign);

    	    char* psub =X509_NAME_oneline(X509_get_subject_name(x509), 0, 0); //get Subject information
            if (psub)
            {
                printf("Subject: %s\n", psub);
                OPENSSL_free(psub);
            }

            char* pis = X509_NAME_oneline(X509_get_issuer_name(x509), 0, 0); //get Issuer information
            if (pis)
            {
                printf("Issuer: %s\n", pis);
                OPENSSL_free(pis);
            }

            X509_free(x509);
        }
    }
    
    fclose(f);
    return 0;
}
