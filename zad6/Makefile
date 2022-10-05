lib_compile:
	gcc -Wall -pedantic -std=c99 -g -Isem_lib -Isem_lib/include -lpthread -c -o build/libsem.a sem_lib/sem_lib.c

fork_exec:
	gcc -Wall -pedantic -std=c99 -g -Iforkexec -Isem_lib/include -Lbuild -lsem -lpthread -o build/fork_exec forkexec/fork_exec.c

wykluczanie:
	gcc -Wall -pedantic -std=c99 -Iwykl -Isem_lib/include -Lbuild -lsem -lpthread -o build/wykluczanie wykl/wykluczanie.c

all: lib_compile fork_exec wykluczanie
