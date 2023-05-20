#include <iostream>
#include <vector>

using namespace std;

struct Graph {
    vector<size_t> parent;
    vector<size_t> group_size;
    size_t num_group, max_group_size;

    Graph(size_t n)
        : parent(n), group_size(n, 1), num_group{n}, max_group_size{1} {
        for (size_t i = 0; i < num_group; i++) parent[i] = i;
    }

    auto find(size_t n) -> size_t {
        return n == parent[n] ? n : find(parent[n]);
    }

    auto merge(size_t u, size_t v) -> void {
        auto u_root{find(u)};
        auto v_root{find(v)};

        if (u_root == v_root) return;

        if (group_size[u_root] > group_size[v_root]) swap(u_root, v_root);

        parent[u_root] = v_root;
        group_size[v_root] += group_size[u_root];

        if (max_group_size < group_size[v_root])
            max_group_size = group_size[v_root];

        num_group--;
    }
};

auto main() -> int {
    size_t num_node, num_edge;
    cin >> num_node >> num_edge;

    // Initialize
    Graph graph(num_node);

    while (num_edge--) {
        size_t u, v;
        cin >> u >> v;
        graph.merge(u - 1, v - 1);

        cout << graph.num_group << " " << graph.max_group_size << "\n";
    }

    return 0;
}