#include <string>
#include <vector>

class ShortestPathGraph;
class PathEntry;

class ShortestPathGraph: public Graph {
	public:
	ShortestPathGraph(Graph& g, std::string from);
	std::deque<PathEntry> path(std::string to);
};

struct PathEntry {
	int metric;
	std::shared_ptr<Node> node;
	std::shared_ptr<Edge> in_edge;
	bool operator>(const DistEntry& b) const;	
};
