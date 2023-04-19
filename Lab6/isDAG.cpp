#include <iostream>
#include <vector>

using namespace std;

class Graph {
    int num_node{};
    vector<vector<int>> adjacent{};

   public:
    Graph(int n) : num_node{n}, adjacent(n) {}

    auto connect(int u, int v) -> void { adjacent[v].emplace_back(u); }

    auto dfs(int node, vector<bool> &visited, vector<bool> &inPath) -> bool {
        // If node has been visited in this path
        if (inPath[node]) return false;

        // If node has been visited but is in other recursion
        if (visited[node]) return true;

        visited[node] = true;
        inPath[node] = true;

        // If no parent, loop will not active
        for (auto parent : adjacent[node])
            // If the graph is not DAG before, just return the result
            if (!dfs(parent, visited, inPath)) return false;

        // Node might be other path ancestor, but it does not mean it is cycle
        inPath[node] = false;
        return true;
    }

    auto isDAG() -> bool {
        vector<bool> visited(num_node, false);
        vector<bool> inPath(num_node, false);

        for (int node = 0; node < num_node; node++)
            if (!dfs(node, visited, inPath)) return false;

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