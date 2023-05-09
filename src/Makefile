CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRC=c_main.c
PFLAGS=$(shell pkg-config --libs --cflags check)
OBJ=c_main.o
TLIBS=-lcheck -lm -lpthread

all: gcov_report

gcov_report: test
	$(CC) $(CFLAGS) --coverage test.c $(SRC) $(TLIBS) -o gcov_test $(PFLAGS)
	@chmod +x *
	@./gcov_test
	@lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	@genhtml -o report/ gcov_test.info
	@open report/index.html

c_main.a:
	$(CC) $(CFLAGS) -c $(SRC) $(PFLAGS)
	ar rcs c_main.a $(OBJ)

test: c_main.a
	$(CC) -c $(SRC) -o $(OBJ) $(PFLAGS)
	$(CC) test.c c_main.a -lcheck -lm -lpthread -o test $(PFLAGS)
	./test

clean:
	rm -rf *.o *.a test *.info *.gcno *.gcda test_output gcov_test report

dvi:
	open readme.html

install:
	rm -rf build
	mkdir build
	cd s21_Calculator && qmake && make && mv s21_Calculator.app ../build && cd ..

uninstall:
	rm -rf build*
	rm -rf s21_Calculator/moc*
	rm -rf s21_Calculator/*.o
	rm -rf s21_Calculator/ui*

dist: install
	rm -rf Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/src
	cp -r ./build/s21_Calculator.app Archive_calc_v1.0/src/
	tar cvzf Archive_calc_v1.0.tgz Archive_calc_v1.0/
	rm -rf Archive_calc_v1.0/