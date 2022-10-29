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
    if(mpz_probab_prime_p(p,200) == 2 && mpz_probab_prime_p(q,200) == 2){
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

    //Defining and initializing mpz variables
    mpz_t c; mpz_init(c);
    mpz_t n; mpz_init(n);
    mpz_t d; mpz_init(d);
    mpz_t b; mpz_init(b);


    //Opening the keyfile in read mode
    FILE* fp = fopen(keyFile, "r");
    //Checking if the file exist or not.
    if (fp == NULL) {
        printf("File Not Found1!\n");
        exit(1);
    } 
    //Calculating the size of the file
    fseek(fp, 0, SEEK_END);
    long k_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    //Allocating space for n string bigger than its needed.
    n_string = (char*) calloc(k_size,sizeof(char));
    //
    size_t i=0;
    while ((ch = fgetc(fp)) != ' ') {
        n_string[i]=ch;
        i++;
    }
    //Setting n.
    mpz_set_str(n,n_string,10);

    //Allocating space for n string bigger than its needed.
    d_string = (char*) calloc(k_size,sizeof(char));
    i=0;
    while ((ch = fgetc(fp)) != EOF) {
        d_string[i]=ch;
        i++;
    }         
    mpz_set_str(d,d_string,10);

    //Read the message to be enrypted from the input file.
    FILE* fp1 = fopen(inputFile, "r");
    //Checking if the file exist or not
    if (fp1 == NULL) {
        printf("File Not Found!\n");
        exit(1);
    }
    
    fseek(fp1, 0, SEEK_END);
    long f_size = ftell(fp);
    fseek(fp1, 0, SEEK_SET);

    
    plaintext = (char*)calloc(f_size,sizeof(char));
     if(plaintext == NULL){
        printf("Error");
    }
    fgets(plaintext, f_size, fp1);

    //Write the encoded chaacters to the output file
    FILE* fp2 = fopen(outputFile, "w");
    //Checking if the file exist or not
    if (fp2 == NULL) {
        printf("File Not Found!\n");
        exit(1);
    }

    for(size_t p =0; p<f_size; p++){
        mpz_set_ui(b,plaintext[p]);
        mpz_powm(c,b,d,n);
        // gmp_printf("%Zd\n",c);
        // gmp_printf("%Zd\n",b);
        // gmp_printf("%Zd\n",d);
        // gmp_printf("%Zd\n",n);
        gmp_fprintf(fp2,"%Zd ",c);
    }

    //Free the space occupied
    mpz_clear(c);
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



}