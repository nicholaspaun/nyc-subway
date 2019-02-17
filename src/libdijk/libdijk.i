%module libdijk
%{
#include "graph.hh"
#include "shortestpath.hh"
%}

%include <std_string.i>
%include <std_deque.i>
%include <std_shared_ptr.i>
%include <std_vector.i>
%shared_ptr(Node)
%shared_ptr(Edge)
%include "graph.hh"
%include "shortestpath.hh"
%template(Path) std::deque<PathEntry>;
