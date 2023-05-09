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
        auto &pos{search(n)};
        if (not pos) {
            pos = make_unique<Node>(n);
            size++;
        }
    }

    auto del(int n) -> void {
        if (del_helper(n, root)) size--;
    }

    auto search(int n) -> unique_ptr<Node> & { return search_helper(n, root); }

    auto lower_bound(int n) -> int {
        auto curr{root.get()};
        int lb{-1};

        while (curr) {
            if (n < curr->val) {
                lb = lb == -1 ? curr->val : min(curr->val, lb);
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
                ub = ub == -1 ? curr->val : min(curr->val, ub);
                curr = curr->left.get();
            } else if (n >= curr->val) {
                curr = curr->right.get();
            }
        }
        return ub;
    }

    auto get_size() -> int { return size; }

   private:
    auto search_helper(int n, unique_ptr<Node> &node) -> unique_ptr<Node> & {
        if (node == nullptr or n == node->val)
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
            auto &sub_max{find_max(node->left)};
            sub_max->right = std::move(node->right);
            node = std::move(sub_max);
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
            auto &node = bst.search(val);
            if (not node)
                cout << "NO\n";
            else
                cout << "YES\n";
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