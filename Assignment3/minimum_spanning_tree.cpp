#include <iostream>
#include <vector>

using namespace std;

struct Graph {
    struct Node {
        size_t idx;
        vector<pair<shared_ptr<Node>, size_t>> adj;

        Node(size_t n) : idx{n} {}
    };

    vector<shared_ptr<Node>> node_ptr;

    Graph(size_t n) {
        node_ptr.reserve(n);
        for (size_t i = 0; i < n; i++)
            node_ptr.emplace_back(make_shared<Node>(i));
    }

    auto connect(size_t u, size_t v, size_t w) -> void {
        auto &U = node_ptr[u];
        auto &V = node_ptr[v];

        U->adj.emplace_back(V, w);
        V->adj.emplace_back(U, w);
    }

    auto display() -> void {
        for (auto ptr : node_ptr) {
            cout << "Node: " << ptr->idx + 1 << "\n";
            for (auto edge : ptr->adj)
                cout << "  " << edge.first->idx + 1 << " " << edge.second
                     << "\n";
        }
    }
};

auto main() -> int {
    size_t num_node, num_edge;
    cin >> num_node >> num_edge;

    Graph g(num_node);
    // Connect graph
    while (num_edge--) {
        size_t u, v, w;
        cin >> u >> v >> w;
        g.connect(u - 1, v - 1, w);
    }

    g.display();
    return 0;
}