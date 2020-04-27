make tp3: malib.o
	gcc -Wall -pedantic -std=c11 tp3.c flop.o malib.o -o tp3

malib.o:
	gcc -Wall -Wextra -pedantic -std=c11 flop.o malib.c -c
	
make:
	./tp3

lib:
	wget -nv https://github.com/guyfrancoeur/INF3135_H2020/raw/master/tp/tp2.zip \-O tp2-v2.zip && unzip -t tp2-v2.zip;
	unzip -q tp2-v2.zip;

clean:
	rm flop.h flop.o tp2-v2.zip malib.o tp3

