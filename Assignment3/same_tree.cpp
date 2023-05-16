#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Node {
    string val{};
    unique_ptr<Node> left, right;

    Node(string val) : val{val}, left{nullptr}, right{nullptr} {}
};

struct Parameter {
    vector<string> &pre;
    vector<string> &in;
    unordered_map<string, size_t> inIndex;
    size_t size, preIdx;

    Parameter(vector<string> &pre, vector<string> &in)
        : pre{pre}, in{in}, size{in.size()}, preIdx{} {
        inIndex.reserve(size);
        for (size_t i = 0; i < in.size(); i++) inIndex[in[i]] = i;
    }
};

auto isPreInSame(vector<string> &pre, vector<string> &in) -> bool;
auto construct(Parameter &param, ssize_t start, ssize_t end)
    -> unique_ptr<Node>;
auto get_post() -> vector<string>;

auto buildTree(vector<string> &pre, vector<string> &in) -> unique_ptr<Node> {
    if (not isPreInSame(pre, in)) return nullptr;

    Parameter param(pre, in);
    return construct(param, 0, param.size - 1);
}

auto isPreInSame(vector<string> &pre, vector<string> &in) -> bool {
    auto root = pre.front();
    unordered_set<string> atLeft;
    for (auto var : in) {
        atLeft.emplace(var);
        if (var == root) break;
    }

    bool same = true;
    for (size_t i = 0; i < atLeft.size(); i++) {
        if (atLeft.find(pre[i]) == atLeft.end()) {
            same = false;
            break;
        }
    }

    return same;
}

auto construct(Parameter &param, ssize_t start, ssize_t end)
    -> unique_ptr<Node> {
    if (start > end) return nullptr;

    auto inIdx = param.inIndex[param.pre[param.preIdx]];
    auto new_node = make_unique<Node>(param.in[inIdx]);

    param.preIdx++;

    new_node->left = construct(param, start, inIdx - 1);
    new_node->right = construct(param, inIdx + 1, end);

    return new_node;
}

auto getPost(unique_ptr<Node> &root) -> vector<string> {
    stack<unique_ptr<Node>> next;
    vector<string> post;
    next.emplace(std::move(root));

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

auto isPostSame(vector<string> &post, vector<string> &new_post) -> bool {
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

        auto root = buildTree(pre, in);
        if (not root) {
            cout << "no\n";
            continue;
        }

        auto new_post = getPost(root);

        if (isPostSame(post, new_post))
            cout << "yes\n";
        else
            cout << "no\n";
    }

    return 0;
}