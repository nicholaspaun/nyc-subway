#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

class Graph;
struct Node;
struct Edge;
class ShortestPathGraph;

class Graph: public std::enable_shared_from_this<Graph> {
	private:
	std::unordered_map<std::string,std::shared_ptr<Node>> nodes;

	public:
	Graph& add_node(std::string id, std::string name);
	Graph& add_edge(std::string name, std::string from, std::string to, int metric);
	std::shared_ptr<Node> node_at(const std::string& id);
	ShortestPathGraph path_from(const std::string& from);	
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
