/*
 * Certificate generation demo
 *
 * Certificate generation demo program
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
#include <openssl/conf.h>
#include <openssl/x509v3.h>

int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days);

int main(int argc, char **argv)
{
	BIO *bio_err;
	X509 *x509=NULL;
	EVP_PKEY *pkey=NULL;
	FILE *fppriv, *fpcerti;

	mkcert(&x509,&pkey,1024,0,365);

	RSA_print_fp(stdout,pkey->pkey.rsa,0);  //print rsa key 
	X509_print_fp(stdout,x509);         
        
	fppriv= fopen("/home/root/privatekey.pem","w");    //create a private key file
	fpcerti = fopen("/home/root/certificate.pem","w"); //create a certificate file
	PEM_write_PrivateKey(stdout,pkey,NULL,NULL,0,NULL, NULL); //write a private key to stdout
	PEM_write_PrivateKey(fppriv,pkey,NULL,NULL,0,NULL, NULL); //write a private key to fppriv
	PEM_write_X509(fpcerti,x509);  //write certificate in certificate.pem
	PEM_write_X509(stdout,x509);   //write certificate to stdout
	fclose(fppriv);
	fclose(fpcerti);

	X509_free(x509);
	EVP_PKEY_free(pkey);

	return(0);
}

static void callback(int p, int n, void *arg)
{
	char c='B';

	if (p == 0) c='.';
	if (p == 1) c='+';
	if (p == 2) c='*';
	if (p == 3) c='\n';
	fputc(c,stderr);
}

/*
*   generate certificate
*/

int mkcert(X509 **x509p, EVP_PKEY **pkeyp, int bits, int serial, int days)
{
	X509 *x;
	EVP_PKEY *pk;
	RSA *rsa;
	X509_NAME *name=NULL;
	
	if ((pkeyp == NULL) || (*pkeyp == NULL))
		{
		if ((pk=EVP_PKEY_new()) == NULL)
			{
			abort(); 
			return(0);
			}
		}
	else
		pk= *pkeyp;

	if ((x509p == NULL) || (*x509p == NULL))
		{
		if ((x=X509_new()) == NULL)
			goto err;
		}
	else
		x= *x509p;

	rsa=RSA_generate_key(bits,RSA_F4,callback,NULL);
	if (!EVP_PKEY_assign_RSA(pk,rsa))
		{
		abort();
		goto err;
		}
	rsa=NULL;

	X509_set_version(x,2);
	ASN1_INTEGER_set(X509_get_serialNumber(x),serial);
	X509_gmtime_adj(X509_get_notBefore(x),0);
	X509_gmtime_adj(X509_get_notAfter(x),(long)60*60*24*days);
	X509_set_pubkey(x,pk);

	name=X509_get_subject_name(x);

	/* This function creates and adds the entry, working out the
	 * correct string type and performing checks on its length.
	 */
	X509_NAME_add_entry_by_txt(name,"C",
				MBSTRING_ASC, "US", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"ST",
				MBSTRING_ASC, "Texas", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"L",
				MBSTRING_ASC, "Dallas", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"O",
				MBSTRING_ASC, "Texas Instruments", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"OU",
				MBSTRING_ASC, "ARM MPU", -1, -1, 0);
	X509_NAME_add_entry_by_txt(name,"CN",
				MBSTRING_ASC, "Sitara User/emailAddress=SitaraUser@ti.com", -1, -1, 0);
  

	/* Its self signed so set the issuer name to be the same as the
 	 * subject.
	 */
	X509_set_subject_name(x,name);
        
	X509_set_issuer_name(x,name);

	
	if (!X509_sign(x,pk,EVP_md5()))
		goto err;

	*x509p=x;
	*pkeyp=pk;
	return(1);
err:
	return(0);
}

