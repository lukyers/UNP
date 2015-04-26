targets = daytimecpcli
cc = gcc
INCLUDES = -I"../sock/"
LIBS = -L"../sock/"

all: $(targets)

daytimecpcli: daytimecpcli.c ../sock/liberr.a
	$(cc) -o daytimecpcli daytimecpcli.c $(LIBS) -lerr $(INCLUDES)
../sock/liberr.a: ../sock/error.c ../sock/error.h ../sock/common.h
	cd ../sock && make

clean:
	rm -rf $(targets) *.o
