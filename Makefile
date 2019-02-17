default: pathfinder gc_routes

pathfinder: bin/_libdijk.so bin/pathfinder.py
	-ln -s bin/pathfinder.py pathfinder
bin/_libdijk.so: src/libdijk/dijk.cc src/libdijk/graph.hh src/libdijk/shortestpath.hh bin/libdijk_wrap.cxx
	cp src/libdijk/graph.hh src/libdijk/shortestpath.hh bin/
	c++ -std=c++17 -shared `pkg-config --cflags --libs python3` src/libdijk/dijk.cc bin/libdijk_wrap.cxx -o bin/_libdijk.so

bin/libdijk_wrap.cxx: src/libdijk/graph.hh src/libdijk/shortestpath.hh src/libdijk/libdijk.i
	swig -c++ -python -o bin/libdijk_wrap.cxx -outdir bin/ src/libdijk/libdijk.i

bin/pathfinder.py: src/query/pathfinder.py bin/csvql.py
	cp -a src/query/pathfinder.py bin/

bin/csvql.py: src/query/csvql.py
	cp src/query/csvql.py bin/

gc_routes: bin/gc_routes.py
	-ln -s bin/gc_routes.py gc_routes
bin/gc_routes.py: bin/csvql.py
	cp -a src/query/gc_routes.py bin/gc_routes.py

clean:
	- rm -r pathfinder gc_routes bin/*
