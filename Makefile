default:tp3

tp3: malib.o
	gcc -Wall -pedantic -std=c11 tp3.c ./data/flop.o malib.o -o tp3

malib.o:
	gcc -Wall -Wextra -pedantic -std=c11 malib.c -c
	
test-tp3:
	./tp3

lib:
	mkdir data
	wget -nv https://github.com/guyfrancoeur/INF3135_H2020/raw/master/tp/tp2.zip -O ./data/tp2-v2.zip
	unzip -n -q ./data/tp2-v2.zip -d ./data

clean:
	rm -r data
	rm malib.o tp3

