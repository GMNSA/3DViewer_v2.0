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
	rm -rf ./tests/libBin
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
ifeq ($(shell file tests/BUILD/), tests/BUILD/: directory)
	$(info Directory does exist)
	cd tests/BUILD && cmake .. && make && ctest && make make_coverage
else
	cd tests && mkdir -p BUILD && cd BUILD && cmake .. && make && ctest && make make_coverage
endif
	./tests/BUILD/bin_test/tst_viewer

tests_open:
ifeq ($(OS), Linux)
	firefox ./tests/BUILD/coverage_report/Model/index.html
else
	open ./tests/BUILD/coverage_report/Model/index.html
endif

check:
	@echo "processing ..."
	./clang_custom.sh n
	echo "~~~ $@ DONE ~~~"

fix:
	echo "processing ..."
	./clang_custom.sh n
	echo "~~~ $@ DONE ~~~"
