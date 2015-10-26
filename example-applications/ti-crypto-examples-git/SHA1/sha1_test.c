/*
 * SHA1 digest demo
 *
 * SHA1 digest demo program using OpenSSL EVP apis
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
 #include <openssl/evp.h>
 #include <openssl/engine.h>

 main(int argc, char *argv[])
 {
 EVP_MD_CTX mdctx;
 const EVP_MD *md;
 FILE *fp, *fpout, *fprnd, *fptmp;
 size_t bytes;
 char *filename="rnddata";
 
 unsigned char mystring[8192];
 unsigned char md_value[EVP_MAX_MD_SIZE];
 int md_len, i;
 
/******************Enabling use of a hardware engine*******************/
 ENGINE *e;

 ENGINE_load_builtin_engines();
 if (!(e = ENGINE_by_id("cryptodev")))
 	fprintf(stderr, "Error finding specified ENGINE\n");
 else if (!ENGINE_set_default(e, ENGINE_METHOD_ALL))
	fprintf(stderr, "Error using ENGINE\n");
 else
	fprintf(stderr, "Engine successfully enabled\n");
/**********************************************************************/

 fp=fopen(filename, "rb");    
  //generate a random file if it doesn't exsit 
 if (fp == NULL) {
       printf ("%s can't be opened.\n", filename);
       printf ("Creating 10M random data file (rnddata)\n");
       system("dd if=/dev/urandom of=rnddata bs=1048576 count=10");
       fp = fopen(filename, "rb");
       if(fp == NULL){
 		printf ("%s Error for file opening!\n", filename);       
 		return 0;
        }
   }   
 
 

 md = EVP_sha1();  // set SHA1 message digest

 EVP_MD_CTX_init(&mdctx);  // initializes digest context mdctx
 EVP_DigestInit_ex(&mdctx, md, e);  //sets up digest context mdctx to use a digest SHA1  
 while ((bytes = fread (mystring, 1, 8192, fp)) != 0)
        EVP_DigestUpdate(&mdctx, mystring, bytes); // hashes "bytes" of data at "mystring" into the digest context mdctx. This function can be called several times on the same mdctx to hash additional data.
 EVP_DigestFinal_ex(&mdctx, md_value, &md_len);  //retrieves the digest value from mdctx and places it in md_value
 EVP_MD_CTX_cleanup(&mdctx);

 printf("Digest is: ");
 for(i = 0; i < md_len; i++) printf("%02x", md_value[i]);  //print digest value
 printf("\n");
 fclose(fp);
 /* Release the structural reference from ENGINE_by_id() */
 ENGINE_free(e);
 
 return 0;

 }
