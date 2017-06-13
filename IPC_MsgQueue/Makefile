server_=server
client_=client
cc=gcc
cliSrc=client.c comm.c
serSrc=server.c comm.c

.PHONY:all
all:$(client_) $(server_)

$(client_): $(cliSrc)
	$(cc) -o $@ $^
$(server_):$(serSrc)
	$(cc) -o $@ $^

.PHONY:clean
clean:
	rm -f $(client_) $(server_)
