#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct DST {
    vector<size_t> parent;
    vector<size_t> group_size;

    DST(size_t num_node) : group_size(num_node, 1) {
        parent.reserve(num_node);
        for (size_t i = 0; i < num_node; i++) parent.emplace_back(i);
    }

    auto find(size_t n) -> size_t {
        return n == parent[n] ? n : find(parent[n]);
    }

    auto merge(size_t u, size_t v) -> bool {
        auto root_u = find(u), root_v = find(v);

        if (root_u == root_v) return false;

        // root_u must the root of larger group
        if (group_size[root_u] < group_size[root_v]) swap(root_u, root_v);
        parent[root_v] = root_u;

        group_size[root_u] += group_size[root_v];
        return true;
    }
};

struct Edge {
    size_t u, v, w;
    Edge(size_t u, size_t v, size_t w) : u{u}, v{v}, w{w} {}
};

auto edge_less(Edge e1, Edge e2) -> bool { return e1.w < e2.w; }

auto main() -> int {
    size_t num_node, num_edge;
    cin >> num_node >> num_edge;

    DST g(num_node);
    vector<Edge> edge;
    edge.reserve(num_edge);
    size_t total_weight{};

    // Connect graph
    while (num_edge--) {
        size_t u, v, w;
        cin >> u >> v >> w;

        edge.emplace_back(u - 1, v - 1, w);
    }

    sort(edge.begin(), edge.end(), edge_less);

    for (auto e : edge) {
        auto [u, v, w] = e;
        if (g.merge(u, v)) total_weight += w;
    }

    cout << total_weight << "\n";

    return 0;
}