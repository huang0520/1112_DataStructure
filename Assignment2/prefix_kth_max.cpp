#include <iostream>
#include <queue>
#include <vector>

using namespace std;

auto main() -> int {
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    int seq_len, k;
    cin >> seq_len >> k;

    priority_queue<int, vector<int>, greater<int>> kth_arr;

    for (int tmp, i = 0; i < k; i++) {
        cin >> tmp;
        kth_arr.emplace(tmp);
    }

    for (int tmp, i = k; i <= seq_len; i++) {
        cout << kth_arr.top() << "\n";

        cin >> tmp;
        kth_arr.emplace(tmp);

        kth_arr.pop();
    }

    return 0;
}