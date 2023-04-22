#include <array>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
    struct node {
        vector<int> parent{};
        vector<int> child{};
    };

    int num_node{};
    vector<node> adj_{};

   public:
    Graph(int n) : num_node{n}, adj_(n, node{}) {}

    auto connect(int u, int v) -> void {
        adj_[u].child.emplace_back(v);
        adj_[v].parent.emplace_back(u);
    }

    // Kahn algorithm
    auto isDAG() -> bool {
        vector<int> inDegree(num_node);
        queue<int> next_visit{};
        int visited = 0;

        // Find number of parents of the node
        int i = 0;
        for (auto &node : adj_) {
            inDegree[i] = node.parent.size();
            i++;
        }

        // Find the source of graph
        i = 0;
        for (auto &in : inDegree) {
            if (in == 0) next_visit.emplace(i);
            i++;
        }

        while (!next_visit.empty()) {
            auto curr = next_visit.front();
            next_visit.pop();

            // Reduce the inDegree of the node connecting to the node who's
            // inDegree is 0
            for (auto child : adj_[curr].child) {
                inDegree[child]--;
                if (inDegree[child] == 0) next_visit.emplace(child);
            }
            visited++;
        }

        if (visited != num_node)
            return false;
        else
            return true;
    }
};

auto main() -> int {
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Read number of cells and number of operation
    int num_node, num_edge;
    cin >> num_node >> num_edge;

    // Build up graph
    Graph graph{num_node};

    // Connect the node
    while (num_edge--) {
        int u, v;
        cin >> u >> v;
        graph.connect(v - 1, u - 1);
    }

    if (graph.isDAG())
        cout << "YES\n";
    else
        cout << "NO\n";

    return 0;
}