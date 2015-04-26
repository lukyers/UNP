targets = tcpserv1
cc = gcc

all: $(targets)

$(targets): $(targets).c ../sock/libunp.a
	$(cc) -o $(targets) $(targets).c ../sock/libunp.a

clean:
	rm -rf $(targets) *.o
