#include <deque>
#include <iostream>
#include <queue>

using namespace std;

class Graph {
   public:
    Graph(int n) : adjacent(deque<deque<int>>(n)) {}

    auto connect(int u, int v) -> void {
        adjacent[u].emplace_back(v);
        adjacent[v].emplace_back(u);
    }

    auto display(/* argument */) -> void {
        for (int i{}; i < adjacent.size(); i++) {
            cout << "Node: " << i + 1;
            for (auto j : adjacent[i]) cout << " Edge: " << j + 1 << " ";
            cout << "\n";
        }
    }

    deque<deque<int>> adjacent{};
};

// Check is there any node hasn't be found
auto check(deque<bool> &found) -> int {
    for (int i{}; i < found.size(); i++) {
        if (!found[i]) return i;
    }

    return -1;
}

auto find_num_component(Graph graph) -> int {
    deque<bool> found(graph.adjacent.size());
    queue<int> next_find;
    int curr_node{}, n_component{};

    while (curr_node >= 0) {
        // Stand at the current node
        next_find.emplace(curr_node);
        found[curr_node] = true;
        n_component += 1;

        while (!next_find.empty()) {
            // Stand at node in front of next_find
            curr_node = next_find.front();
            next_find.pop();

            // Find the connected node and push into next_find
            for (auto i : graph.adjacent[curr_node]) {
                if (found[i]) continue;

                // Tag the node
                found[i] = true;
                next_find.emplace(i);
            }
        }

        curr_node = check(found);
    }

    return n_component;
}

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

        cout << find_num_component(graph) << "\n";
        // graph.display();
    }

    return 0;
}
