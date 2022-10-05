lcom:
	gcc -Wall -pedantic -std=c99 -Ilibcom -c libcom/libcom.c -o build/libcom.a -lrt

server:
	gcc -Wall -pedantic -std=c99 -Ilibcom -Lbuild -o build/server src/server.c -lcom -lrt

client:
	gcc -Wall -pedantic -std=c99 -Ilibcom -Lbuild -o build/client src/client.c -lcom -lrt

all: lcom server client

run:
	xterm -hold -title SERWER -bg red -e ./build/server &
	sleep .5
	xterm -hold -title KLIENT -bg green -e ./build/client &
	sleep .5
	xterm -hold -title KLIENT -bg green -e ./build/client &
