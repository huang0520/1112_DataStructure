#include <deque>
#include <iostream>
#include <queue>

using namespace std;

class Graph {
    struct node {
        int distance{-1};
        bool have_cookie{false};
        deque<int> adjacent{};
    };

    int num_node{};
    deque<node> adjacent_list{};

   public:
    Graph(int n) : num_node{n}, adjacent_list{deque<node>(n)} {}

    auto connect(int u, int v) -> void {
        adjacent_list[u].adjacent.emplace_back(v);
        adjacent_list[v].adjacent.emplace_back(u);
    }

    auto put_cookie(int n) -> void { adjacent_list[n].have_cookie = true; }

    auto bfs_find_cookie(int root) -> int {
        adjacent_list[root].distance = 0;

        deque<int> next_dis{root};
        deque<bool> found(num_node, false);

        for (int curr{root}, dis{0}; !next_dis.empty(); dis++) {
            // Push node at the current distance in queue
            queue<int> next_find{next_dis};
            next_dis.clear();

            // Find the node at the next distance and push into deque
            // Tag the found node and denote the distance
            while (!next_find.empty()) {
                curr = next_find.front();
                next_find.pop();

                // If curr node have cookie return curr distance
                if (adjacent_list[curr].have_cookie) return dis;

                // Denote the distance of curr node
                adjacent_list[curr].distance = dis;

                // Push adjacent node of curr node into next dis deque
                for (auto i : adjacent_list[curr].adjacent) {
                    if (found[i]) continue;

                    found[i] = true;
                    next_dis.emplace_back(i);
                }
            }
        }

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

        int dis = graph.bfs_find_cookie(root - 1);

        if (dis == -1)
            cout << "SAD\n";
        else
            cout << dis << "\n";
    }

    return 0;
}