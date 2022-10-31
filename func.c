#include"func.h"

void generateKeys(){
    mpz_t p,q,n,lambda_n,p_n,q_n,e,tmp1,tmp2,d; 

    //Initializing mpz variables.
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

    //Reading primes from command line.
    printf("Enter a prime number for p:");
    gmp_scanf("%Zd",p);

    printf("Enter a prime number for q:");
    gmp_scanf("%Zd",q);

    //Checking if the numbers entered are prime. The function doesn't always find if a number is prime when the number is 30-40 digits.
    if(mpz_probab_prime_p(p,50) == 2 && mpz_probab_prime_p(q,50) == 2){
        //Initialize e to 2.
        mpz_set_ui(e,2);
        //Calculate n.
        mpz_mul(n,p,q);
        mpz_sub_ui(p_n,p,1);
        mpz_sub_ui(q_n,q,1);
        //Calculate lambda.
        mpz_mul(lambda_n,p_n,q_n);

        //Choosing e.
        while(mpz_cmp(e,lambda_n)<0){
            mpz_gcd(tmp2,e,lambda_n);
            if( mpz_cmp_ui(tmp2,1) != 0 ){
                mpz_add_ui(e,e,1);
            }
            else{
                //Calculating d.
                mpz_invert(d,e,lambda_n);

                //Open file public.key with write permissions and write the generated key.
                FILE *fp;
                fp = fopen("public.key", "w");
                if(fp == NULL){
                    printf("Error opening file!");   
                    exit(1);             
                }
                gmp_fprintf(fp,"%Zd %Zd",n ,d);
                fclose(fp);

                //Open file private.key with write permissions and write the generated key.
                fp = fopen("private.key", "w");
                if(fp == NULL){
                    printf("Error opening file!");   
                    exit(1);             
                }
                gmp_fprintf(fp,"%Zd %Zd",n ,e);
                fclose(fp);

                //Free the space occupied.
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


void encryptMessage( char* inputFile, char* outputFile,char * keyFile){
    char ch;
    char *plaintext,*n_string,*d_string;

    //Defining and initializing mpz variables.
    mpz_t C; mpz_init(C);
    mpz_t n; mpz_init(n);
    mpz_t d; mpz_init(d);
    mpz_t b; mpz_init(b);


    //Opening the keyfile in read mode.
    FILE* fp = fopen(keyFile, "r");
    //Checking if the file exist or not.
    if (fp == NULL) {
        printf("File Not Found1!\n");
        exit(1);
    } 
    //Calculating the size of the file.
    fseek(fp, 0, SEEK_END);
    long k_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    //Allocating space for n string bigger than its needed, to be sure it fits.
    n_string = (char*) calloc(k_size,sizeof(char));
    //
    size_t i=0;
    while ((ch = fgetc(fp)) != ' ') {
        n_string[i]=ch;
        i++;
    }
    //Setting n.
    mpz_set_str(n,n_string,10);

    //Allocating space for d string bigger than its needed, to be sure it fits.
    d_string = (char*) calloc(k_size,sizeof(char));
    //Reseting i for next loop
    i=0;
    while ((ch = fgetc(fp)) != EOF) {
        d_string[i]=ch;
        i++;
    }   
    //Setting d.      
    mpz_set_str(d,d_string,10);

    //Read the message to be enrypted from the input file.
    FILE* fp1 = fopen(inputFile, "r");
    //Checking if the file exist or not.
    if (fp1 == NULL) {
        printf("File Not Found!\n");
        exit(1);
    }
    
    fseek(fp1, 0, SEEK_END);
    long f_size = ftell(fp1);
    fseek(fp1, 0, SEEK_SET);

    
    plaintext = (char*)calloc(f_size,sizeof(char));
     if(plaintext == NULL){
        printf("Error");
    }

    //Not sure what problem has fgets but fread ficed the problem
    //fgets(plaintext, f_size, fp1);
    fread(plaintext, sizeof(char), f_size, fp1);

    //Write the encoded characters to the output file.
    FILE* fp2 = fopen(outputFile, "w");
    //Checking if the file exist or not
    if (fp2 == NULL) {
        printf("File Not Found!\n");
        exit(1);
    }

    for(size_t p =0; p<f_size; p++){
            ch = plaintext[p];
            mpz_set_ui(b,ch);
            mpz_powm(C,b,d,n);
            //gmp_printf("%Zd\n",C);
            // gmp_printf("%Zd\n",b);
            // gmp_printf("%Zd\n",d);
            // gmp_printf("%Zd\n",n);
            gmp_fprintf(fp2,"%Zd ",C);
        
    }

    //Free the space occupied.
    mpz_clear(C);
    mpz_clear(n);
    mpz_clear(d);
    mpz_clear(b);
    free(plaintext);
    //Close file descriptors.
    fclose(fp);
    fclose(fp2);
    fclose(fp1);

}


void decryptMessage(char* inputFile, char* outputFile, char* keyFile){
    char ch;
    char *n_string,*e_string;
    //int tmp[1];
    

    //Defining and initializing mpz variables.
    mpz_t D; mpz_init(D);
    mpz_t n; mpz_init(n);
    mpz_t e; mpz_init(e);
    mpz_t b; mpz_init(b);

    //Opening the keyfile in read mode.
    FILE* fp = fopen(keyFile, "r");
    //Checking if the file exist or not.
    if (fp == NULL) {
        printf("File Not Found1!\n");
        exit(1);
    } 
    //Calculating the size of the file.
    fseek(fp, 0, SEEK_END);
    long k_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    //Allocating space for n string bigger than its needed, to be sure it fits.
    n_string = (char*) calloc(k_size,sizeof(char));
    size_t i=0;
    while ((ch = fgetc(fp)) != ' ') {
        n_string[i]=ch;
        i++;
    }
    //Setting n.
    mpz_set_str(n,n_string,10);


    //Allocating space for e string bigger than its needed, to be sure it fits.
    e_string = (char*) calloc(k_size,sizeof(char));
    //Reseting i for next loop
    i=0;
    while ((ch = fgetc(fp)) != EOF) {
        e_string[i]=ch;
        i++;
    }     
    //Setting e.    
    mpz_set_str(e,e_string,10);


    //Read the message to be decrypted from the input file.
    FILE* fp1 = fopen(inputFile, "r");
    //Checking if the file exist or not.
    if (fp1 == NULL) {
        printf("File Not Found!\n");
        exit(1);
    }
    

    //Write the decoded chaacters to the output file.
    FILE* fp2 = fopen(outputFile, "w");
    //Checking if the file exist or not
    if (fp2 == NULL) {
        printf("File Not Found!\n");
        exit(1);
    }
    //Decrypt message and write to output file.
    while(mpz_inp_str(b, fp1, 10) ){
        //printf("%Zd\n",b);
        mpz_powm(D, b, e, n);
        //gmp_printf("%Zd",D);
        ch = mpz_get_ui(D);
        //printf("\n%c",ch);
		fprintf(fp2,"%c", ch);
    }

    //printf("here:%lu",mpz_inp_str(b, fp1, 10));


     //Free the space occupied.
    mpz_clear(D);
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(b);
    //Close file descriptors.
    fclose(fp);
    fclose(fp2);
    fclose(fp1);

}



bool file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    bool is_exist = false;
    if (fp != NULL)
    {
        is_exist = true;
        fclose(fp); //Close the file descriptor
    }
    return is_exist;
}