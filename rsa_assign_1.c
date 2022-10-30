#include"func.h"

int main(int argc, char *argv[] )  {  
   int opt;
   char * inputFile,*outputFile,*keyFile;
    // Put ':' in the beginning of the string so that program can 
    //distinguish between '?' and ':' .
    while((opt = getopt(argc, argv,":i:o:k:degh")) != -1) 
    { 
        switch(opt) 
        { 
            case 'i': 
                //Getting input filename and checking if the file already exists.If it doesnt it creates it.
                printf("Input filename: %s\n", optarg);
                inputFile = (char *)malloc((strlen(optarg)+1)*sizeof(char));
                if (inputFile == NULL){
                  puts("Memory allocation error.");
                  return 1;
                }
                strcpy(inputFile,optarg);
                if(!file_exists(inputFile)){
                    FILE *fp = fopen(inputFile, "w");
                    if(fp == NULL)
                        exit(1);
                    fclose(fp);
                }
                else
                    continue;
                break; 
            case 'o': 
                //Getting output filename and checking if the file already exists.If it doesnt it creates it.
                printf("Output filename: %s\n", optarg);
                outputFile = (char *)malloc((strlen(optarg)+1)*sizeof(char));
                if (outputFile == NULL){
                  puts("Memory allocation error.");
                  return 1;
                }
                strcpy(outputFile,optarg);
                if(!file_exists(outputFile)){
                    FILE *fp = fopen(outputFile, "w");
                    if(fp == NULL)
                        exit(1);
                    fclose(fp);
                }
                else
                    continue;

                break; 
            case 'k': 
                //Getting key filename and checking if the file already exists.If it doesnt it creates it.
                printf("Key filename: %s\n", optarg);
                keyFile = (char *)malloc((strlen(optarg)+1)*sizeof(char));
                if (keyFile == NULL){
                  puts("Memory allocation error.");
                  return 1;
                }
                strcpy(keyFile,optarg);
                if(!file_exists(keyFile)){
                    FILE *fp = fopen(keyFile, "w");
                    if(fp == NULL)
                        exit(1);
                    fclose(fp);
                }
                else
                    continue;

                break; 
            case 'g': 
                generateKeys();
                printf("Key generation executed!");
                break;
            case 'd': 
                decryptMessage(inputFile,outputFile,keyFile);
                printf("Message encryption executed!");

                free(inputFile);
                free(outputFile);
                free(keyFile);
                break;
            case 'e': 
                encryptMessage(inputFile,outputFile,keyFile);
                printf("Decryption executed!\n");

                free(inputFile);
                free(outputFile);
                free(keyFile);
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
    //Optind is for the extra arguments which are not parsed.
    for(; optind < argc; optind++){     
        printf("extra arguments: %s\n", argv[optind]); 
    }


 }