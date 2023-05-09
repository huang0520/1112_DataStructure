#include <iostream>
#include <memory>
#include <queue>

using namespace std;

class BST {
    struct Node {
        int val{};
        unique_ptr<Node> left;
        unique_ptr<Node> right;

        Node(int n) : val{n}, left{nullptr}, right{nullptr} {}
    };

    unique_ptr<Node> root{nullptr};
    int size{};

   public:
    BST() {}

    auto ins(int n) -> void {
        auto new_node = make_unique<Node>(n);
        if (ins_node(new_node)) size++;
    }

    auto del(int n) -> void {
        if (del_helper(n, root)) size--;
    }

    auto search(int n) -> bool { return search_helper(n, root) ? true : false; }

    auto lower_bound(int n) -> int {
        auto curr{root.get()};
        int lb{-1};

        while (curr) {
            if (n < curr->val) {
                lb = curr->val;
                curr = curr->left.get();
            } else if (n > curr->val) {
                curr = curr->right.get();
            } else {
                lb = curr->val;
                break;
            }
        }
        return lb;
    }

    auto upper_bound(int n) -> int {
        auto curr{root.get()};
        int ub{-1};

        while (curr) {
            if (n < curr->val) {
                ub = curr->val;
                curr = curr->left.get();
            } else if (n >= curr->val) {
                curr = curr->right.get();
            }
        }
        return ub;
    }

    auto get_size() -> int { return size; }

   private:
    auto ins_node(unique_ptr<Node> &node) -> bool {
        auto &pos = search_helper(node->val, root);
        if (not pos) {
            pos = std::move(node);
            return true;
        }
        return false;
    }

    auto search_helper(int n, unique_ptr<Node> &node) -> unique_ptr<Node> & {
        if (not node or n == node->val)
            return node;
        else {
            return search_helper(n, n < node->val ? node->left : node->right);
        }
    }

    auto del_helper(int n, unique_ptr<Node> &node) -> bool {
        // not found the node that has value n
        if (not node) return false;

        if (n != node->val)
            return del_helper(n, n < node->val ? node->left : node->right);

        // node has no child or only right
        if (not node->left) node = std::move(node->right);

        // node has 2 child or only left
        else {
            auto tmp_right{std::move(node->right)};
            node = std::move(node->left);
            find_max(node)->right = std::move(tmp_right);
        }

        return true;
    }

    auto find_max(unique_ptr<Node> &node) -> unique_ptr<Node> & {
        if (node->right)
            return find_max(node->right);
        else
            return node;
    }
};

auto main() -> int {
    int num_op;
    cin >> num_op;

    BST bst{};

    while (num_op--) {
        char op;
        int val;
        cin >> op >> val;

        if (op == 'I') {
            bst.ins(val);
            cout << bst.get_size() << "\n";
        }

        else if (op == 'D') {
            bst.del(val);
            cout << bst.get_size() << "\n";
        }

        else if (op == 'S') {
            if (bst.search(val))
                cout << "YES\n";
            else
                cout << "NO\n";
        }

        else if (op == 'L') {
            cout << bst.lower_bound(val) << "\n";
        }

        else if (op == 'U') {
            cout << bst.upper_bound(val) << "\n";
        }
    }

    return 0;
}