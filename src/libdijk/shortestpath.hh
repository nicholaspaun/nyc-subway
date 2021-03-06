#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <deque>
#include <functional>

class ShortestPathGraph;
struct PathEntry;

struct PathEntry {
	int metric;
	std::shared_ptr<Node> node;
	std::shared_ptr<Edge> out_edge;
	bool operator>(const PathEntry& b) const;	
};

class ShortestPathGraph {
	private:
	std::priority_queue<PathEntry,std::vector<PathEntry>,std::greater<PathEntry>> pq;
	std::unordered_map<std::string, PathEntry> prev;
	std::unordered_set<std::string> visited;
	std::shared_ptr<Graph> g;

	public:
	ShortestPathGraph(std::shared_ptr<Graph> g, const std::string& from);
	std::deque<PathEntry> to(const std::string& to);
};

