includes = tiernan.h tarjan.h johnson.h
objects = tiernan.o tarjan.o johnson.o
sources = tiernan.c tarjan.c johnson.c
out = tiernan tarjan johnson

all: $(objects) tiernan tarjan johnson

$(objects): $(includes)

tarjan: 
	cc -o tarjan tarjan.o -lm -lpthread

tiernan:
	cc -o tiernan tiernan.o -lm -lpthread

johnson: 
	cc -o johnson johnson.o -lm -lpthread
.PHONY: clean 
clean:
	rm -f $(out) $(objects)
