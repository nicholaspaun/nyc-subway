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
%shared_ptr(Graph)
%include "graph.hh"
%include "shortestpath.hh"
%ignore std::enable_shared_from_this<Graph>;
%template(Path) std::deque<PathEntry>;
