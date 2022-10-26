#include<stdio.h>
#include<gmp.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>



void generateKeys(){
    mpz_t p,q,n,lambda_n,p_n,q_n,e,tmp1,tmp2,d; 

    mpz_init(p);
    mpz_init(q);
    mpz_init (n);
    mpz_init (lambda_n);
    mpz_init (p_n);
    mpz_init (q_n);
    mpz_init (e);
    mpz_init (tmp1);
    mpz_init (tmp2);
    mpz_init (d);

    printf("Enter a prime number for p:");
    gmp_scanf("%Zd",p);

    printf("Enter a prime number for q:");
    gmp_scanf("%Zd",q);

    if(mpz_probab_prime_p(p,100) == 2 && mpz_probab_prime_p(q,200) == 2){
   // if(1 && 1){
        mpz_set_ui(e,2);
        mpz_mul(n,p,q);
        mpz_sub_ui(p_n,p,1);
        mpz_sub_ui(q_n,q,1);
        mpz_mul(lambda_n,p_n,q_n);
        gmp_printf("here\n");
        while(mpz_cmp(e,lambda_n)<0){
            mpz_mod(tmp1,e,lambda_n);
            mpz_gcd(tmp2,e,lambda_n);
            if(mpz_cmp_ui(tmp1,0) == 0 || mpz_cmp_ui(tmp2,1) != 0){
                mpz_add_ui(e,e,1);
            }
            else{
                gmp_printf("e at the end:%Zd\n",e);
                mpz_invert(d,e,lambda_n);
                gmp_printf("d:%Zd",d);
                FILE *fp;
                fp = fopen("public.key", "w");
                if(fp == NULL){
                    printf("Error!");   
                    exit(1);             
                }
                gmp_fprintf(fp,"%Zd%Zd",n ,d);
                fclose(fp);
                
                fp = fopen("private.key", "w");
                if(fp == NULL){
                    printf("Error!");   
                    exit(1);             
                }
                gmp_fprintf(fp,"%Zd%Zd",n ,e);
                fclose(fp);

                mpz_clear(p);
                mpz_clear(q);
                mpz_clear(n);
                mpz_clear(lambda_n);
                mpz_clear(p_n);
                mpz_clear(q_n);
                mpz_clear(e);
                mpz_clear(tmp1);
                mpz_clear(tmp2);
                mpz_clear(d);
                break;
            }
        }
    }
    else{
        printf("The numbers you entered are not prime!");
    } 
}

int main(int argc, char *argv[] )  {  
   int opt;
   char * inputFile,*outputFile,*keyFile;
    // put ':' in the starting of the
    // string so that program can 
    //distinguish between '?' and ':' 
    while((opt = getopt(argc, argv,":i:o:k:d:e:gh")) != -1) 
    { 
        switch(opt) 
        { 
            case 'i': 
                printf("Input filename: %s\n", optarg);
                inputFile = (char *)malloc((strlen(optarg)+1)*sizeof(char));
                if (inputFile == NULL){
                  puts("Memory allocation error.");
                  return 1;
                }
                strcpy(inputFile,optarg);
                break; 
            case 'o': 
                printf("Output filename: %s\n", optarg);
                outputFile = (char *)malloc((strlen(optarg)+1)*sizeof(char));
                if (outputFile == NULL){
                  puts("Memory allocation error.");
                  return 1;
                }
                strcpy(outputFile,optarg);
                break; 
            case 'k': 
                printf("Key filename: %s\n", optarg);
                keyFile = (char *)malloc((strlen(optarg)+1)*sizeof(char));
                if (keyFile == NULL){
                  puts("Memory allocation error.");
                  return 1;
                }
                strcpy(keyFile,optarg);

                break; 
            case 'g': 
                generateKeys();
                break;
            case 'd': 
                printf("option: %s\n", optarg); 

                break;
            case 'e': 
                printf("option: %s\n", optarg); 

                break; 
                
            case 'h': 
                printf("The arguments “i”, “o” and “k” are always required when using “e” or “d”\nUsing -i and a path the user specifies the path to the input file.\nUsing -o and a path the user specifies the path to the output file.\nUsing -k and a path the user specifies the path to the key file.\nUsing -g the tool generates a public and a private key and stores them to the public.keyand private.key files respectively.\nUsing -d the user specifies that the tool should read the ciphertext from the input file,decrypt it and then store the plaintext in the output file.Using -e the user specifies that the tool should read the plaintext from the input file,encrypt it and store the ciphertext in the output file.");
                return 1;
            case ':': 
                printf("option needs a value\n"); 
                break; 
            case '?': 
                printf("unknown option: %c\n", optopt);
                break; 
        } 
    } 
    // optind is for the extra arguments
    // which are not parsed
    for(; optind < argc; optind++){     
        printf("extra arguments: %s\n", argv[optind]); 
    }
 }
