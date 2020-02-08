tp1: tp1.c flop.o
	gcc -Wall -pedantic -std=c11 -I/usr/include/CUnit -L/usr/lib64 -lcunit -o tp1 ./tp1.c ./data/flop.o
clean:
	rm tp1
	rm liste.sh
test:
	./tp1 | grep -F '...passed'| sed -e 's/^/echo /' > liste.sh
	chmod +x ./liste.sh
lib:
	wget https://github.com/guyfrancoeur/INF3135_H2020/raw/master/tp/tp1.zip -P ./data/	
