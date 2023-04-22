#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Graph {
    struct node {
        vector<int> child{};
        vector<int> parent{};
    };

    int num_node{};
    vector<long long> value{};
    vector<node> adjacent{};

   public:
    Graph(int n) : num_node{n}, value(n, 0), adjacent(n, node{}) {}

    auto connect(int u, int v) -> void {
        adjacent[v].parent.emplace_back(u);
        adjacent[u].child.emplace_back(v);
    }

    auto assign_val(int n, int val) -> void { value[n] = val; }

    auto print_cells_value() -> void {
        vector<int> inDegree(num_node);
        queue<int> next_visit{};

        // Calculate in degree of nodes
        for (int i = 0; i <= num_node - 1; i++) {
            inDegree[i] = adjacent[i].parent.size();

            // If node has no parent push in to queue
            if (inDegree[i] == 0) next_visit.emplace(i);
        }

        // Kahn algorithm
        while (!next_visit.empty()) {
            auto curr = next_visit.front();
            next_visit.pop();

            for (auto child : adjacent[curr].child) {
                // Remove edge between curr node
                inDegree[child]--;

                // Add the curr value to its child
                value[child] += value[curr];

                // If in degree of child = 0, push into queue
                if (inDegree[child] == 0) next_visit.emplace(child);
            }
        }

        // Print the cell value
        for (int i = 0; i <= num_node - 1; i++) {
            if (inDegree[i] == 0)
                cout << value[i] << "\n";
            else
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

    graph.print_cells_value();

    return 0;
}