#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
Direct graph
    adjacent list
node:
    int index
    int value = 0
    list parent
    bool visited = false
*/
class Graph {
    struct node {
        node() {}
        node(int n) : index{n} {}
        vector<int> parent{};
        bool visited = false;
        int val{}, index{};
    };

    int num_node{};
    vector<node> adjacent{};

   public:
    Graph(int n) : adjacent(n) {
        for (int i = 0; i < n; i++) adjacent[i] = node{i};
    }

    auto connect(int u, int v) -> void { adjacent[v].parent.emplace_back(u); }

    auto assign_val(int n, int val) -> void { adjacent[n].val = val; }

    auto display() -> void {
        int i = 1;
        for (auto &node : adjacent) {
            cout << "Node " << i << " val: " << node.val << " parent cell:";
            for (auto cell : node.parent) cout << " " << cell + 1;
            cout << "\n";
            i++;
        }
    }

    /*
    Traverse the node and do DFS along parents
    if no parent:
        safe
    if parent has been visited:
        parent safe: safe, val += parent val
        parent unsafe: unsafe, val = -1
    if parent has not been visited, do DFS on parent.
    */
    auto dfs(node &node, vector<int> &history) -> int {
        // If node has been visited in this recursion
        if (find(history.begin(), history.end(), node.index) != history.end()) {
            // Node unsafe
            node.val = -1;
            return -1;
        }

        history.emplace_back(node.index);

        // If node has been visited but is in other recursion
        if (node.visited) return node.val;

        // Node hasn't been visited
        node.visited = true;

        // No parent
        if (node.parent.empty()) return node.val;

        // Has parent
        for (auto cell : node.parent) {
            // Get parent value
            int val = dfs(adjacent[cell], history);

            // Parent unsafe, node also unsafe
            // Parent safe, plus it value to node value
            if (val == -1) {
                node.val = -1;
                return node.val;
            } else {
                node.val += val;
                continue;
            }
        }
        return node.val;
    }

    auto print_cell_value() -> void {
        vector<bool> visited{};
        for (auto node : adjacent) {
            // Node has been visited
            if (node.visited and node.val != -1) {
                cout << node.val << "\n";
                continue;
            } else if (node.visited and node.val == -1) {
                cout << "#REF!\n";
                continue;
            }

            vector<int> history{};
            int val = dfs(node, history);

            if (val != -1)
                cout << node.val << "\n";
            else if (val == -1)
                cout << "#REF!\n";
        }
    }
};

auto main() -> int {
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    // Read number of cells and number of operation
    int num_cell, num_op;
    cin >> num_cell >> num_op;

    // Build up graph
    Graph graph{num_cell};

    // Connect the node and assign y val
    while (num_op--) {
        char op;
        cin >> op;

        int num_val;
        switch (op) {
            case 'A':
                num_val = 2;
                break;

            case 'B':
                num_val = 3;
                break;

            case 'C':
                num_val = 4;
                break;

            case 'D':
                num_val = 5;
                break;
        }

        vector<int> val(num_val, 0);
        for (int i = 0; i < num_val; i++) cin >> val[i];

        // Assign y to node x1
        graph.assign_val(val[0] - 1, *(val.end() - 1));

        for (int i = 1; i < num_val - 1; i++)
            graph.connect(val[i] - 1, val[0] - 1);
    }

    graph.print_cell_value();

    return 0;
}