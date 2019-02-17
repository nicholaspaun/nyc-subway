#include <string>
#include <vector>
#include <unordered_map>

class Graph;
class Node;
class Edge;
class ShortestPathGraph;

class Graph {
	private:
	std::unordered_map<std::string,std::shared_ptr<Node>> nodes;

	public:
	Graph& add_node(std::string id, std::string name);
	Graph& add_edge(std::string name, std::string from, std::string to, int metric);
	std::shared_ptr<Node> node_at(std::string id);
	ShortestPathGraph path_from(std::string from);	
};

struct Node {
	std::string id;
	std::string name;
	std::vector<std::shared_ptr<Edge>> adj;
};

struct Edge {
	std::string name;
	int metric;
	std::weak_ptr<Node> to;
};
