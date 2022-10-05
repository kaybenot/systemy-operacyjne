Napisane przez Kamila Butryna.

Kompilacja:
    Dla danego programu należy uruchomić komendę `make`
     z argumentem od `exec_zaj`

Uruchamianie:
    Pliki do wykonywalne znajdują się w folderze `build`.
     Należy wejść do tego folderu i wpisać `./exec_zaj exec_prog`

Odpowiadając na pytanie, powstaną 3 procesy potomne z funkcji fork-exec,
ponieważ fork stworzy 3 procesy potomne i każdy za pomocą exec'a wykona programu
podany jako argument.
