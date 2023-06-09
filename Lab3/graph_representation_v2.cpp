#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class graph {
   public:
    graph(int num_node) { this->edge_list = deque<deque<int>>(num_node); }

    int degree(int u) { return this->edge_list[u - 1].size(); }

    auto neighbor(int u, int v) -> char {
        auto& i = this->edge_list[u - 1];
        if (find(i.begin(), i.end(), v) != i.end())
            return 'Y';
        else
            return 'N';
    }

    void connect(int u, int v) {
        this->edge_list[u - 1].emplace_back(v);
        this->edge_list[v - 1].emplace_back(u);
    }

   private:
    deque<deque<int>> edge_list;
};

int main(void) {
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Read input
    int num_node, num_edge, num_query;
    cin >> num_node >> num_edge >> num_query;

    // Construct the adjacency list
    graph G(num_node);

    // Connect the node
    while (num_edge--) {
        int u, v;
        cin >> u >> v;
        G.connect(u, v);
    }

    // Query
    while (num_query--) {
        char op;
        cin >> op;

        if (op == 'D') {
            int val;
            cin >> val;

            cout << G.degree(val) << '\n';
        } else if (op == 'N') {
            int u, v;
            cin >> u >> v;

            cout << G.neighbor(u, v) << '\n';
        }
    }
}