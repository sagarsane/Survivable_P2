includes = tiernan.h tarjan.h
objects = tiernan.o tarjan.o
sources = tiernan.c tarjan.c
out = tiernan tarjan

all: $(objects) tiernan tarjan

$(objects): $(includes)

tarjan: 
	cc -o tarjan tarjan.o -lm -lpthread

tiernan:
	cc -o tiernan tiernan.o -lm -lpthread

#vertex: 
#	cc -o vertex_disjoint vertex_disjoint.o vertex_util.o -lm -lpthread
.PHONY: clean 
clean:
	rm -f $(out) $(objects)
