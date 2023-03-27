#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class MinHeap {
   private:
    auto __insert_arrange(int pos) -> void {
        if (this->__heap[pos / 2] < this->__heap[pos] or pos / 2 == 0) return;

        swap(this->__heap.at(pos / 2), this->__heap.at(pos));

        __insert_arrange(pos / 2);
    }

    auto __remove_arrange(int pos) -> void {
        int length = this->__heap.size() - 1;
        int left = pos * 2;
        int right = pos * 2 + 1;
        int target;

        bool left_exist = left <= length;
        bool right_exist = right <= length;

        if (left_exist and this->__heap[left] < this->__heap[pos])
            target = left;
        else
            target = pos;

        if (right_exist and this->__heap[right] < this->__heap[target])
            target = right;

        if (target != pos) {
            swap(this->__heap.at(pos), this->__heap.at(target));
            __remove_arrange(target);
        }
    }

    vector<int> __heap;

   public:
    MinHeap() { this->__heap = vector<int>(1, 0); }

    auto insert(int val) -> void {
        this->__heap.emplace_back(val);
        __insert_arrange(this->__heap.size() - 1);
    }

    auto remove_min() -> void {
        if (this->__heap.size() == 1) return;

        swap(this->__heap.at(1), this->__heap.at(this->__heap.size() - 1));
        this->__heap.pop_back();

        __remove_arrange(1);
    }

    auto find_min() -> int { return this->__heap.at(1); }
};

auto main() -> int {
    // Read input
    int num_op;
    cin >> num_op;

    MinHeap heap;

    while (num_op--) {
        int op;
        cin >> op;

        switch (op) {
            case 1:
                int val;
                cin >> val;
                heap.insert(val);
                break;

            case 2:
                heap.remove_min();
                break;

            case 3:
                try {
                    cout << heap.find_min() << "\n";
                } catch (out_of_range &e) {
                    cout << "EMPTY\n";
                }
                break;

            default:
                break;
        }
    }

    return 0;
}