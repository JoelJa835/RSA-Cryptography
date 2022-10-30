#ifndef RSA_H
#define RSA_H

#include<stdio.h>
#include<gmp.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include   <stdbool.h>



/*
 * Generates a key pair for RSA encryption and saves
 * each key in a different file. The public key is saved in a file "public.key" 
 * and the private key in a file "private.key"
 */
void generateKeys();

/*
 * Encrypts an input file with plain text in it and writes the ciphertext into the output file
 */
void encryptMessage(char* inputFile, char* outputFile, char* keyFile);

/*
 * Decrypts the input file with the ciphertext in it and writes the decoded text into the output file
 */
void decryptMessage(char* inputFile, char* outputFile, char* keyFile);


/*
 * Checks if a file exists and returns boolean depending on the situation
 */
bool file_exists(const char *filename);


#endif