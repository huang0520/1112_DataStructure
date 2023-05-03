#include <iostream>
#include <memory>
#include <stack>
#include <vector>

using namespace std;

struct node {
    node(int n) : index{n} {}

    int index{};
    shared_ptr<node> parent{};
    shared_ptr<node> lchild{};
    shared_ptr<node> rchild{};
};

auto main() -> int {
    int num_node;
    shared_ptr<node> last;
    stack<shared_ptr<node>> traversal;
    cin >> num_node;

    vector<shared_ptr<node>> tree(num_node);

    for (int i = 1; i < num_node + 1; i++) tree[i - 1] = make_shared<node>(i);

    // Connect tree
    for (auto &node : tree) {
        int l, r;
        cin >> l >> r;

        if (l != -1) {
            node->lchild = tree[l - 1];
            node->lchild->parent = node;
        }
        if (r != -1) {
            node->rchild = tree[r - 1];
            node->rchild->parent = node;
        }
    }

    // Find root and push to stack
    for (auto &node : tree)
        if (node->parent == nullptr) traversal.emplace(node);

    // Preorder traversal
    while (!traversal.empty()) {
        auto curr = traversal.top();
        traversal.pop();

        if (curr->rchild != nullptr) traversal.emplace(curr->rchild);
        if (curr->lchild != nullptr) traversal.emplace(curr->lchild);

        last = curr;
    }

    cout << last->index << "\n";

    return 0;
}