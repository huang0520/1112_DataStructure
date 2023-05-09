#include <iostream>
#include <memory>
#include <queue>

using namespace std;

class BST {
    struct Node {
        int val{};
        shared_ptr<Node> parent;
        unique_ptr<Node> left;
        unique_ptr<Node> right;

        Node(int n) : val{n}, left{nullptr}, right{nullptr}, parent{nullptr} {}
    };

    unique_ptr<Node> root{nullptr};
    int size{};

   public:
    BST() {}

    auto ins(int n) -> void {
        auto &pos = search(n);
        if (pos == nullptr) pos = make_unique<Node>(n);

        size++;
    }

    auto del(int n) -> void {}

    auto search(int n) -> unique_ptr<Node> & { return search_helper(n, root); }

    auto lower_bound(int n) -> int { /* code */
    }

    auto upper_bound(int n) -> int { /* code */
    }

    auto size() -> int { return size; }

   private:
    auto search_helper(int n, unique_ptr<Node> &ptr) -> unique_ptr<Node> & {
        if (ptr == nullptr or n == ptr->val)
            return ptr;
        else if (n > ptr->val)
            return search_helper(n, ptr->right);
        else
            return search_helper(n, ptr->left);
    }
};

auto main() -> int {
    int num_op;
    cin >> num_op;

    BST bst{};

    if (!bst.search(5)) cout << "NO\n";

    return 0;
}