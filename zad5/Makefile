pro_kons_naz_a:
	gcc pro_kons.c -o pro_kons
	gcc pro_kons_naz.c -o pro_kons_naz

pro_kons_naz_b:
	gcc producent.c -o producent
	gcc konsument.c -o konsument

run_a:
	./pro_kons_naz potok
	diff -s produkty.txt surowce.txt

run_b:
	mkfifo -m 777 potok
	xterm -hold -title PRODUCENT-KONSUMENT -e ./producent potok &
	xterm -hold -title PRODUCENT-KONSUMENT -e ./konsument potok
	unlink potok
	
