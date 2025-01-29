vpcc = gcc -std=c99 -g -Wall -Wextra -Wpedantic -Wbad-function-cast \
        -Wconversion -Wwrite-strings -Wstrict-prototypes -Wshadow

.PHONY : all

all : isemptydir

isemptydir : isemptydir.c isemptydir.help

%.help : %.txt
	sed -E 's/^/"/;s/$$/\\n"/' $< > $@

% : %.c
	$(vpcc) -o $@ $<
	strip $@
