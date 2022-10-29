CC=gcc  #compiler
CFLAGS = -Wall
LDFLAGS = -lgmp
OBJFILES = rsa_assign_1.o util.o func.o
TARGET=rsa_assign_1 #target file name
 
all:$(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
 
clean:
	rm -rf $(OBJFILES) $(TARGET) *~
