#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <memory>

class ShortestPathGraph;
class PathEntry;

class ShortestPathGraph {
	private:
	std::priority_queue<PathEntry,std::vector<PathEntry>,std::greater<PathEntry>> pq;
	std::unordered_map<std::string, PathEntry> prev;
	std::unordered_set<std::string> visited;
	Graph& g;

	public:
	ShortestPathGraph(Graph& g, std::string from);
	std::deque<PathEntry> to(std::string to);
};

struct PathEntry {
	int metric;
	std::shared_ptr<Node> node;
	std::shared_ptr<Edge> out_edge;
	bool operator>(const PathEntry& b) const;	
};
