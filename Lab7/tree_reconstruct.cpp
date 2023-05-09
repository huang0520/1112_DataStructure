#include <algorithm>
#include <iostream>
#include <memory>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
    struct TreeNode {
        int val;
        unique_ptr<TreeNode> left;
        unique_ptr<TreeNode> right;
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    };

    unordered_map<int, int> inIndex;
    int preIdx = 0;

   public:
    auto construct(vector<int> &pre, vector<int> &in, int start, int end)
        -> unique_ptr<TreeNode> {
        if (start > end) return nullptr;

        int inIdx = inIndex[pre[preIdx]];
        auto new_node = make_unique<TreeNode>(in[inIdx]);

        preIdx++;

        new_node->left = construct(pre, in, start, inIdx - 1);
        new_node->right = construct(pre, in, inIdx + 1, end);

        return new_node;
    }

    auto build(vector<int> &pre, vector<int> &in) -> unique_ptr<TreeNode> {
        for (int i = 0; i < (int)pre.size(); i++) inIndex[in[i]] = i;
        return construct(pre, in, 0, (int)pre.size() - 1);
    }

    auto post(unique_ptr<TreeNode> &root) -> void {
        stack<unique_ptr<TreeNode>> next;
        next.emplace(move(root));

        while (!next.empty()) {
            auto &curr = next.top();

            if (!curr->left and !curr->right) {
                cout << curr->val << " ";
                next.pop();
                continue;
            }

            if (curr->right) next.emplace(move(curr->right));
            if (curr->left) next.emplace(move(curr->left));
        }
        return;
    }
};

auto main() -> int {
    int num_node;
    cin >> num_node;

    vector<int> pre(num_node), in(num_node);

    for (auto &var : pre) cin >> var;
    for (auto &var : in) cin >> var;

    Solution sol;
    auto root = sol.build(pre, in);
    sol.post(root);

    return 0;
}