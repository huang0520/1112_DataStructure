#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
    struct node {
        vector<int> adj_node{};
        bool hasCookie{false};
    };

    vector<node> adj_{};
    vector<int> distance{};

   public:
    Graph(int n) : adj_(n, node{}), distance(n, -1) {}

    auto connect(int u, int v) -> void {
        adj_[u].adj_node.emplace_back(v);
        adj_[v].adj_node.emplace_back(u);
    }

    auto put_cookie(int n) -> void { adj_[n].hasCookie = true; }

    auto cookie_dis(int root) -> int {
        // Store the visited node
        vector<bool> visited(adj_.size(), false);

        queue<int> next_find{};
        next_find.emplace(root);

        // Set the distance of root node 0
        distance[root] = 0;

        while (!next_find.empty()) {
            int curr = next_find.front();
            next_find.pop();

            // If the current node has cookie return its distance to root
            if (adj_[curr].hasCookie) return distance[curr];

            // visited the adjacent node and denote their distance as which of
            // current node + 1
            for (auto node : adj_[curr].adj_node) {
                if (visited[node]) continue;

                visited[node] = true;
                distance[node] = distance[curr] + 1;
                next_find.emplace(node);
            }
        }

        // If the component which root on has no cookies
        return -1;
    }
};

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

        int dis = graph.cookie_dis(root - 1);

        if (dis == -1)
            cout << "SAD\n";
        else
            cout << dis << "\n";
    }

    return 0;
}