#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
    int num_node{};
    vector<vector<int>> adjacent_list{};
    vector<bool> cookie{};
    vector<int> distance{};

   public:
    Graph(int n)
        : num_node{n}, adjacent_list(n), cookie(n, false), distance(n, -1) {}

    auto connect(int u, int v) -> void {
        adjacent_list[u].emplace_back(v);
        adjacent_list[v].emplace_back(u);
    }

    auto adjacent(int n) -> const vector<int>& { return adjacent_list[n]; }
    auto put_cookie(int n) -> void { cookie[n] = true; }
    auto is_cookie(int n) -> bool { return cookie[n]; }
    auto set_dis(int n, int dis) -> void { distance[n] = dis; }
    auto dis(int n) -> int { return distance[n]; }
    auto size() -> int { return num_node; }
};

auto bfs_find_cookie(Graph& graph, int root) -> int {
    vector<bool> found(graph.size(), false);

    queue<int> next_find{};
    next_find.emplace(root);

    int curr{}, dis{};
    graph.set_dis(root, 0);

    while (!next_find.empty()) {
        curr = next_find.front();
        next_find.pop();

        dis = graph.dis(curr);

        if (graph.is_cookie(curr)) return dis;

        for (auto i : graph.adjacent(curr)) {
            if (found[i]) continue;

            found[i] = true;
            graph.set_dis(i, dis + 1);
            next_find.emplace(i);
        }
    }

    return -1;
}

auto main() -> int {
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    int num_test;
    cin >> num_test;

    while (num_test--) {
        // Read number of node, number of edge
        int num_node, num_edge, num_cookie, root;
        cin >> num_node >> num_edge;

        Graph graph{num_node};

        // Connect edge
        while (num_edge--) {
            int u, v;
            cin >> u >> v;

            graph.connect(u - 1, v - 1);
        }

        // Read the root node
        cin >> root;

        // Read the cookie node and put cookie
        cin >> num_cookie;

        while (num_cookie--) {
            int n;
            cin >> n;

            graph.put_cookie(n - 1);
        }

        int dis = bfs_find_cookie(graph, root - 1);

        if (dis == -1)
            cout << "SAD\n";
        else
            cout << dis << "\n";
    }

    return 0;
}