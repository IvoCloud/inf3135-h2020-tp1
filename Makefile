make:
	gcc -Wall -pedantic -std=c11 tp2.c flop.o -o tp2

make test-tp2:
	./TP2

make lib:
	wget -nv https://github.com/guyfrancoeur/INF3135_H2020/raw/master/tp/tp2.zip \-O tp2-v2.zip && unzip -t tp2-v2.zip

make clean:
	rm ./TP2

