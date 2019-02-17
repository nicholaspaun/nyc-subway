default: pathfinder gc_routes

pathfinder: bin/_libdijk.so

bin/_libdijk.so: src/libdijk/dijk.cc src/libdijk/graph.hh src/libdijk/shortestpath.hh bin/libdijk_wrap.cxx
	cp src/libdijk/graph.hh src/libdijk/shortestpath.hh bin/
	c++ -std=c++2a -shared `pkg-config --cflags --libs python3` src/libdijk/dijk.cc bin/libdijk_wrap.cxx -o bin/_libdijk.so

bin/libdijk_wrap.cxx: src/libdijk/graph.hh src/libdijk/shortestpath.hh src/libdijk/libdijk.i
	swig -c++ -python -o bin/libdijk_wrap.cxx -outdir bin/ src/libdijk/libdijk.i

gc_routes:

clean:
	- rm bin/*
