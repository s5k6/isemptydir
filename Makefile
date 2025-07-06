vpcc = gcc -std=c99 -g -Wall -Wextra -Wpedantic -Wbad-function-cast \
        -Wconversion -Wwrite-strings -Wstrict-prototypes -Wshadow

.PHONY : dflt all test clean distclean

dflt : isemptydir

all : test clean

clean :
	rm -rf isemptydir.help testcases/

distclean : clean
	rm -f isemptydir

test : isemptydir
	./testsuite

isemptydir : isemptydir.c isemptydir.help

%.help : %.txt
	sed -E 's/^/"/;s/$$/\\n"/' $< > $@

% : %.c
	$(vpcc) -o $@ $<
	strip $@
