Napisane przez Kamila Butryna.

Kompilacja:
    Dla danego programu należy uruchomić komendę `make`
     z argumentem od `procesy_a` do `procesy_e`,
     w zależności od zadania.

Uruchamianie:
    Pliki do wykonywalne znajdują się w folderze `build`.
     Należy je uruchomić z poziomu konsoli,
     wpisując odpowiednio ich nazwy.

Opisy zadań:
A: Wypisuje podane w zadaniu identyfikatory.
B: Za pomocą instukcji switch identyfikuje procesy po wykonaniu `fork()`,
    każdy podproces czeka na swoje procesy funkcją `wait()`.
C: Procesy potomne używają funkcji `sleep(30)`,
    aby stać się procesami zombie poprzez zakończenie się
    procesu macierzystego podczas ich działania.
D: Zadanie B z dopiską sleep i wartością identyfikującą procesy
    potomne. Umożliwia to wypisanie wyniku procesu macierzystego
    na końcu. W pliku drzewo.txt zawarte jest "drzewo genealogiczne"
    procesów.
E: Zadanie takie jak B, tylko procesy potomne ustawiają swój PGID na
    wartość swojego PID za pomocą `setpgid(0, 0)`, przez co stają się
    liderami swoich grup procesów.
