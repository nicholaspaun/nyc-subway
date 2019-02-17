#include "graph.hh"
#include "shortestpath.hh"
#include <iostream>

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

ShortestPathGraph Graph::path_from(string from) {
	return ShortestPathGraph(*this, from);
}

ShortestPathGraph::ShortestPathGraph(Graph& g, string from) : g(g) {

	// 1. Initialize source
	shared_ptr<Node> source = g.node_at(from);
	pq.push({0,source});
	prev.emplace(source->id, PathEntry{0});

	// 2. Dijkstra's algorithm
	while (!pq.empty()) {
		shared_ptr<Node> u = pq.top().node;
		pq.pop();

		if (visited.count(u->id)) {
			// HACK: It's annoying to remove from the STL priority queue so just ignore attempts to revisit a node
			continue;
		}
		visited.insert(u->id);

		for (auto e: u->adj) {
			shared_ptr<Node> v = e->to.lock();
			int ourMetric = prev[u->id].metric + e->metric;
			if (!prev.count(v->id) || ourMetric < prev[v->id].metric) {
				prev.insert_or_assign(v->id, PathEntry{ourMetric, u, e});
				pq.push({ourMetric, v});
			}
		}
	}
}

std::deque<PathEntry> ShortestPathGraph::to(string dest) {
	std::deque<PathEntry> path;
	PathEntry ent = prev[dest];
	while (ent.node != NULL) {
		int prevDist = prev[ent.node->id].node != NULL ? prev[ent.node->id].metric : 0;
		path.push_front({ent.metric - prevDist, ent.node, ent.out_edge});
		ent = prev[ent.node->id];
	}

	path.push_back({0, g.node_at(dest), make_shared<Edge>(Edge{"Arrived.",0})});
	return path;	
}

bool PathEntry::operator>(const PathEntry& b) const {
	return metric > b.metric;
}

