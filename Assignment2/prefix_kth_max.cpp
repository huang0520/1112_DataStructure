#include <functional>
#include <iostream>
#include <vector>

using namespace std;

auto partition(vector<int> &arr, int left, int right) -> int {
    if (left >= right) return left;

    auto pivot = (left + right) / 2;

    // choose pivot (median of three)
    if (left - right >= 2) {
        auto middle = (left + right) / 2;
        bool a = arr[left] >= arr[middle];
        bool b = arr[middle] >= arr[left];
        bool c = arr[left] >= arr[right];

        // middle is median
        if (a and b) pivot = middle;
        // right is median
        else if ((b and c) or (!b and !c))
            pivot = right;
        // left is median
        else if ((a and c) or (!a and !c))
            pivot = left;
    }

    // swap pivot and rightest element
    swap(arr[pivot], arr[right]);
    pivot = right;

    auto lp = left, rp = right - 1;

    while (true) {
        // Move left pointer until its value larger than pivot
        while (arr[lp] >= arr[pivot] and lp < right) lp++;

        // Move right pointer until its value less than pivot
        while (arr[rp] <= arr[pivot] and rp > left) rp--;

        // Check whether right pointer smaller than left pointer
        if (lp >= rp) {
            swap(arr[lp], arr[pivot]);
            break;
        } else
            swap(arr[lp], arr[rp]);
    }

    return lp;
}

auto kth_max(vector<int> &arr, int k) -> int {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        auto pivot = partition(arr, left, right);

        // pivot is larger than k - 1 numbers
        if (pivot + 1 == k) return arr[pivot];
        // the number of numbers pivot greater than is less than k - 1
        else if (pivot + 1 < k)
            left = pivot + 1;
        // the number of number pivot greater than is more than k - 1
        else
            right = pivot - 1;
    }

    return -1;
}

auto main() -> int {
    int seq_len, k;
    cin >> seq_len >> k;

    vector<int> arr(seq_len);

    for (int tmp, i = 0; i < seq_len; i++) {
        cin >> tmp;
        arr[i] = tmp;
    }

    for (int i = k; i <= seq_len; i++) {
        vector<int> tmp_arr(arr.begin(), arr.begin() + i);
        cout << kth_max(tmp_arr, k) << "\n";
    }

    return 0;
}