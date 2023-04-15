#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Graph {
   public:
    Graph() {}
    Graph(int n) : adjacent(vector<list<int>>(n)) {}

    auto connect(int u, int v) -> void {
        adjacent[u].emplace_back(v);
        adjacent[v].emplace_back(u);
    }

    auto DFS_find() -> int {
        int num_component{};
        visited = vector<bool>(adjacent.size(), false);

        for (int node{}; node < adjacent.size(); node++) {
            if (!visited[node]) {
                num_component += 1;
                DFS(node);
            }
        }
        return num_component;
    }

    auto DFS(int n) -> void {
        visited[n] = true;

        for (auto it : adjacent[n])
            if (!visited[it]) DFS(it);
    }

   private:
    vector<list<int>> adjacent{};
    vector<bool> visited{};
};

auto main() -> int {
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Read number of test
    int num_test{};
    cin >> num_test;

    for (int test{}; test < num_test; test++) {
        // Read number of node & edge
        int num_node{}, num_edge{};
        cin >> num_node >> num_edge;

        Graph graph(num_node);

        // Connect the graph vertices
        for (int edge{}; edge < num_edge; edge++) {
            // Read two connected node
            int u{}, v{};
            cin >> u >> v;

            graph.connect(u - 1, v - 1);
        }

        cout << graph.DFS_find() << "\n";
    }

    return 0;
}