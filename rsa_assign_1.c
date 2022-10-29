#include"func.h"

int main(int argc, char *argv[] )  {  
   int opt;
   char * inputFile,*outputFile,*keyFile;
    // put ':' in the starting of the
    // string so that program can 
    //distinguish between '?' and ':' 
    while((opt = getopt(argc, argv,":i:o:k:degh")) != -1) 
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
                decryptMessage(inputFile,outputFile,keyFile);

                free(inputFile);
                free(outputFile);
                free(keyFile);
                break;
            case 'e': 
                encryptMessage(inputFile,outputFile,keyFile);

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
    // optind is for the extra arguments
    // which are not parsed
    for(; optind < argc; optind++){     
        printf("extra arguments: %s\n", argv[optind]); 
    }


 }