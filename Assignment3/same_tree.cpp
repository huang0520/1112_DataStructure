#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class BST {
    struct Node {
        string val{};
        unique_ptr<Node> left, right;

        Node(string val) : val{val}, left{nullptr}, right{nullptr} {}
    };

    size_t size, preIdx;
    unique_ptr<Node> root;
    unordered_map<string, size_t> inIndex;

   public:
    BST(vector<string> &pre, vector<string> &in) : size{in.size()}, preIdx{} {
        inIndex.reserve(size);
        for (size_t i = 0; i < in.size(); i++) inIndex[in[i]] = i;
        root = construct(pre, in, 0, size - 1);
    }

    auto get_post() -> vector<string> {
        stack<unique_ptr<Node>> next;
        vector<string> post;
        next.emplace(std::move(root));
        post.reserve(size);

        while (!next.empty()) {
            auto &curr = next.top();

            if (!curr->left and !curr->right) {
                post.emplace_back(curr->val);
                next.pop();
                continue;
            }

            if (curr->right) next.emplace(std::move(curr->right));
            if (curr->left) next.emplace(std::move(curr->left));
        }
        return post;
    }

   private:
    auto construct(vector<string> &pre, vector<string> &in, int start, int end)
        -> unique_ptr<Node> {
        if (start > end) return nullptr;

        auto inIdx = inIndex.find(pre[preIdx])->second;
        auto new_node = make_unique<Node>(in[inIdx]);

        preIdx++;

        new_node->left = construct(pre, in, start, inIdx - 1);
        new_node->right = construct(pre, in, inIdx + 1, end);

        return new_node;
    }
};

auto check_same(vector<string> &post, vector<string> &new_post) -> bool {
    for (size_t i = 0; i < post.size(); i++)
        if (post[i] != new_post[i]) return false;

    return true;
}

auto main() -> int {
    size_t num_case;
    cin >> num_case;

    while (num_case--) {
        size_t len;
        cin >> len;

        vector<string> pre(len), in(len), post(len);
        for (size_t i = 0; i < len; i++) cin >> pre[i];
        for (size_t i = 0; i < len; i++) cin >> in[i];
        for (size_t i = 0; i < len; i++) cin >> post[i];

        BST bst(pre, in);
        auto new_post = bst.get_post();

        if (check_same(post, new_post))
            cout << "yes\n";
        else
            cout << "no\n";
    }

    return 0;
}