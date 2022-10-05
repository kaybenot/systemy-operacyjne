Napisane przez Kamila Butryna.

Kompilacja:
    Dla danego programu należy uruchomić komendę `make`
     z argumentem od `sig_a` do `sig_c`,
     w zależności od zadania.

Uruchamianie:
    Pliki do wykonywalne znajdują się w folderze `build`.
     Należy je uruchomić z poziomu konsoli,
     wpisując odpowiednio ich nazwy. (Aby poprawnie je uruchomić należy
     w nim być)
     Czyli np:
     
     `./sig_a [arg1] [arg2]`
     
     arg1 to numer sygnału (np. 2 dla SIGINT)
     arg2 to tryb. Możliwe tryby to:
     	default - domyślna operacja sygnału
     	ignore - ignorowanie sygnału
     	brak argumentu - przechwycenie sygnału

Opisy zadań:
A: Przechwytuje, ignoruje lub ustawia operację domyślną dla sygnału.
    Należy wpisać numer sygnału jako pojedyńczy argument dla przechwytywania.
    Jako drugi argument podać `ignore` albo `default` aby zignorować albo ustawić
    operację domyślną dla sygnału.
B: Uruchamia aplikację z A komendą execl przekierowując do niej argumenty.
    Wysyłany jest przekazany sygnał po 2 sekundach.
C: Uruchamia 3 procesy potomne w procesie potomnym i zwraca jego wartość.
