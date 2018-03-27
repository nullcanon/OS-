.PHONY:all
all:client server

client:client.c shared_men.c 
	gcc -o $@ $^

server:server.c shared_men.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm client server
