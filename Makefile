includes = tiernan.h
objects = tiernan.o
sources = tiernan.c
out = tiernan

all: $(objects) tiernan

$(objects): $(includes)

#dijkstra: 
#	cc -o modified_dijkstra modified_dijkstra.o -lm -lpthread

tiernan:
	cc -o tiernan tiernan.o -lm -lpthread

#vertex: 
#	cc -o vertex_disjoint vertex_disjoint.o vertex_util.o -lm -lpthread
.PHONY: clean 
clean:
	rm -f $(out) $(objects)
