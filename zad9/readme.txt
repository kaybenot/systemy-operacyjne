Napisane przez Kamila Butryna.

Kompilacja:
    Wpisać komendę `make all`.

Uruchamianie:
    W katalogu wpisać `./zad9` z argumentami kolejno oznaczającymi liczbę wątków
     oraz liczbę sekcji krytycznych dla każdego wątku.

Opis zadania:
    Program realizuje wzajemne wykluczanie dla wątków, gdzie wątki początkowo
     wykonują swoje sekcje prywatne na raz, i kolejno wchodzą do sekcji krytycznej
     pojedyńczo. Wyświetlana jest kolejka po lewej stronie terminala o czekających
     wątkach, a po prawej widoczny jest obecnie znajdujący się wątek w sekcji
     krytycznej. Pod koniec sprawdzane jest czy sekcja krytyczna wykonała się 
     odpowiednią ilość razy. Blokowane przy pomocy mutexu.
    
