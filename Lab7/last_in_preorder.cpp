#include <iostream>
#include <stack>
#include <vector>

using namespace std;

auto main() -> int {
    int num_node;
    cin >> num_node;
    vector<pair<ssize_t, ssize_t>> child(num_node, {-1, -1});
    vector<ssize_t> parent(num_node, -1);

    // Construct graph
    for (ssize_t i = 0; i < num_node; i++) {
        ssize_t l, r;
        cin >> l >> r;

        if (l != -1) {
            child[i].first = l - 1;
            parent[l - 1] = i;
        }

        if (r != -1) {
            child[i].second = r - 1;
            parent[r - 1] = i;
        }
    }

    ssize_t ans{};
    stack<ssize_t> traversal;

    // find root
    for (ssize_t i = 0; i < num_node; i++)
        if (parent[i] == -1) traversal.emplace(i);

    // Preorder traversal
    while (!traversal.empty()) {
        auto curr = traversal.top();
        traversal.pop();

        // Push right child first
        // Left child second
        if (child[curr].second != -1) traversal.emplace(child[curr].second);
        if (child[curr].first != -1) traversal.emplace(child[curr].first);

        ans = curr;
    }

    cout << ans + 1 << "\n";

    return 0;
}