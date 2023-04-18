#include <iostream>
#include <vector>

using namespace std;

class Graph {
    int num_node{};
    vector<long long> value{};
    vector<vector<int>> adjacent{};

   public:
    Graph(int n) : num_node{n}, value(n, 0), adjacent(n) {}

    auto connect(int u, int v) -> void { adjacent[v].emplace_back(u); }

    auto assign_val(int n, int val) -> void { value[n] = val; }

    auto dfs(int node, vector<bool> &visited, vector<bool> &inPath)
        -> long long {
        // If node has been visited in this recursion
        if (inPath[node]) {
            // Node unsafe
            value[node] = -1;
            return -1;
        }

        // If node has been visited but is in other recursion
        if (visited[node]) return value[node];

        visited[node] = true;
        inPath[node] = true;

        // If no parent, loop will not active
        for (auto parent : adjacent[node]) {
            // Get parent value
            long long val = dfs(parent, visited, inPath);

            // Parent unsafe, node also unsafe
            // Parent safe, plus it value to node value
            if (val == -1) {
                value[node] = -1;
                break;
            } else
                value[node] += val;
        }

        // Node might be other path ancestor, but it does not mean it is cycle
        inPath[node] = false;
        return value[node];
    }

    auto print_cell_value() -> void {
        vector<bool> visited(num_node, false);
        vector<bool> inPath(num_node, false);

        for (int node = 0; node < num_node; node++) {
            long long val = dfs(node, visited, inPath);

            if (val == -1)
                cout << "#REF!\n";
            else
                cout << val << "\n";
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