CC=gcc  #compiler
TARGET=rsa_assign_1 #target file name
 
all:
	$(CC) rsa_assign_1.c -o $(TARGET) -lgmp
 
clean:
	rm -rf *.o $(TARGET)
