kurrent_os := $(shell sh -c 'uname -s 2>/dev/null || echo not')

ifeq ($(shell uname), Linux)
  OS=Linux
endif

ifeq ($(shell uname), Darwin)
  OS=Darwin
endif


.PHONY: all clean rebuild check test_model tests check fix open tests_open uninstall

all: install start

clean:
	rm -rf ./BUILD
	rm -rf ./tests/BUILD
	rm -rf ./libBin/*

install: checkdir
	cd BUILD && cmake .. && make

uninstall:
	rm -rf ./BUILD

checkdir :
	@echo "checkdir"
	mkdir -p BUILD
	mkdir -p tests/BUILD

dvi:
ifeq ($(OS), Linux)
	firefox dvi.html
else
	open dvi.html
endif

start:
	./BUILD/3DV2

dist:
	tar -cf 3DV2.0.tar ./*

tests:
	cd tests && mkdir -p BUILD && cd BUILD && cmake .. && make && ctest && make make_coverage

tests_open:
ifeq ($(OS), Linux)
	firefox ./tests/BUILD/coverage_report/index.html
else
	open ./tests/BUILD/coverage_report/index.html
endif

check:
	@echo "processing ..."
	./clang_custom.sh n
	echo "~~~ $@ DONE ~~~"

fix:
	echo "processing ..."
	./clang_custom.sh n
	echo "~~~ $@ DONE ~~~"
