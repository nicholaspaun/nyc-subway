#include "graph.hh"

using std::string;
using std::make_shared;
using std::shared_ptr;
using std::weak_ptr;

/*** Graphs ***/
Graph& Graph::add_node(string id, string name) {
	nodes.emplace(id, make_shared<Node>(Node{id, name}));
	return *this;
}

Graph& Graph::add_edge(string name, string from, string to, int metric) {
	nodes.at(from)->adj.push_back(make_shared<Edge>(Edge{name, metric, nodes.at(to)}));
	return *this;
}

shared_ptr<Node> Graph::node_at(string id) {
	return nodes.at(id);
}
