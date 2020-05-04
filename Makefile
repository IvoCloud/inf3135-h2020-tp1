default:tp2

tp2: malib.o
	gcc -Wall -pedantic -std=c11 tp2.c ./data/flop.o malib.o -o tp2

malib.o:
	gcc -Wall -Wextra -pedantic -std=c11 malib.c -c

lib:
	mkdir data
	wget -nv https://github.com/guyfrancoeur/INF3135_H2020/raw/master/tp/tp2.zip -O ./data/tp2-v2.zip
	unzip -q ./data/tp2-v2.zip -d ./data

clean:
	rm -r data
	rm malib.o tp2

