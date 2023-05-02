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
    auto horse_sort() -> void {
        vector<int> sort_arr{};
        vector<int> inDegree(num_node);
        priority_queue<int, vector<int>, greater<int>> next_visit{};
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
            auto curr = next_visit.top();
            next_visit.pop();

            sort_arr.emplace_back(curr);

            // Reduce the inDegree of the node connecting to the node who's
            // inDegree is 0
            for (auto child : adj_[curr].child) {
                inDegree[child]--;
                if (inDegree[child] == 0) next_visit.emplace(child);
            }
            visited++;
        }

        if (visited != num_node)
            cout << -1 << "\n";
        else {
            for (auto i : sort_arr) cout << i + 1 << " ";
            cout << "\n";
        }
    }
};

auto main() -> int {
    // Read number of cells and number of operation
    int num_node, num_edge;
    cin >> num_node >> num_edge;

    // Build up graph
    Graph graph{num_node};

    // Connect the node
    while (num_edge--) {
        int u, v;
        cin >> u >> v;
        graph.connect(u - 1, v - 1);
    }

    graph.horse_sort();

    return 0;
}