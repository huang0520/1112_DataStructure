#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct node {
    int index{};
    node* parent;
    node* lchild;
    node* rchild;

    node() {}
    node(int n) : index{n} {}
};

auto main() -> int {
    int num_node;
    stack<node&> traversal;
    cin >> num_node;

    vector<node*> tree(num_node, new node());

    // Connect tree
    for (int i = 0; i < num_node; i++) {
        int l, r;
        cin >> l >> r;

        tree[i]->index = i + 1;

        if (l != -1) {
            l--;
            tree[l]->parent = tree[i];
        }
        if (r != -1) {
            r--;
            tree[r]->parent = tree[i];
        }

        tree[i] = node{i};
    }

    // Find root and push to stack
    for (int i = 0; i < num_node; i++)
        if (tree[i].parent == -1) traversal.emplace(i);

    // Preorder traversal
    while (!traversal.empty()) {
        auto curr = traversal.top();
        traversal.pop();

        if (tree[curr].child.second != -1)
            traversal.emplace(tree[curr].child.second);
        if (tree[curr].child.first != -1)
            traversal.emplace(tree[curr].child.first);

        last = curr;
    }

    cout << tree[last].index << "\n";

    return 0;
}