#include <iostream>
#include <queue>
#include <vector>

using namespace std;

auto main() -> int {
    int num_op;
    cin >> num_op;

    priority_queue<int, vector<int>, greater<int>> heap;

    while (num_op--) {
        int op;
        cin >> op;

        switch (op) {
            case 1:
                int val;
                cin >> val;

                heap.emplace(val);
                break;

            case 2:
                if (!heap.empty()) heap.pop();
                break;

            case 3:
                if (heap.empty())
                    cout << "EMPTY\n";
                else
                    cout << heap.top() << "\n";
                break;

            default:
                break;
        }
    }

    return 0;
}