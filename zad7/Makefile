lib_static:
	gcc -Wall -pedantic -std=gnu99 -Ilibseg -o build//lib/libseg.a -c libseg/libseg.c -lpthread -lrt

lib_dynamic:
	gcc -Wall -pedantic -std=gnu99 -fPIC -Ilibseg -shared -o build/lib/libseg_dyn.so libseg/libseg.c -lpthread -lrt

producent:
	gcc -Wall -pedantic -std=gnu99 -Ilibseg -Lbuild/lib -o build/producent prog/producent.c -lseg -lrt -lpthread

konsument:
	gcc -Wall -pedantic -std=gnu99 -Ilibseg -Lbuild/lib -o build/konsument prog/konsument.c -lseg -lrt -lpthread

forkexec:
	gcc -Wall -pedantic -std=gnu99 -Ilibseg -Lbuild/lib -o build/forkexec prog/forkexec.c -lseg -lrt -lpthread

all: lib_static producent konsument forkexec lib_dynamic
