.PHONY:all
all:server client


server:server.c message.c
	gcc -o $@ $^

client:client.c message.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm server client
