#include <iostream>
#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

vector<pair<ssize_t, ssize_t>> child;
unordered_map<ssize_t, ssize_t> inIdx_tbl;
ssize_t preIdx{};

auto construct(vector<ssize_t> &pre, vector<ssize_t> &in, ssize_t start,
               ssize_t end) -> ssize_t {
    if (start > end) return -1;

    auto sub_root{pre[preIdx]};
    auto inIdx = inIdx_tbl[sub_root];

    preIdx++;

    child[sub_root].first = construct(pre, in, start, inIdx - 1);
    child[sub_root].second = construct(pre, in, inIdx + 1, end);

    return sub_root;
}

auto display() -> void {
    for (auto [l, r] : child) cout << l + 1 << " " << r + 1 << "\n";
}

auto main() -> int {
    int num_node;
    cin >> num_node;

    vector<ssize_t> pre(num_node), in(num_node);
    child = vector<pair<ssize_t, ssize_t>>(num_node);
    stack<ssize_t> traversal;

    // Read
    for (auto &var : pre) {
        ssize_t n;
        cin >> n;
        var = n - 1;
    }
    for (auto &var : in) {
        ssize_t n;
        cin >> n;
        var = n - 1;
    };

    // Build in index search table
    for (ssize_t i = 0; i < num_node; i++) inIdx_tbl[in[i]] = i;

    auto root = construct(pre, in, 0, pre.size() - 1);
    traversal.emplace(root);

    // display();

    // Postorder
    while (!traversal.empty()) {
        auto curr = traversal.top();

        // If curr has no child print and pop
        if (child[curr].first == -1 and child[curr].second == -1) {
            cout << curr + 1 << " ";
            traversal.pop();
            continue;
        }

        // Push curr rchild(first), lchild and remove them from child list
        if (child[curr].second != -1) {
            traversal.emplace(child[curr].second);
            child[curr].second = -1;
        }
        if (child[curr].first != -1) {
            traversal.emplace(child[curr].first);
            child[curr].first = -1;
        };
    }

    return 0;
}