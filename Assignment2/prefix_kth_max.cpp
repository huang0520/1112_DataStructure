#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;

auto display(vector<int> &arr) -> void {
    for (auto var : arr) {
        cout << var << " ";
    }
    cout << "\n";
}

auto partition(vector<int> &arr, int left, int right, int k) -> int {
    if (left >= right) return arr[left];

    // choose pivot (median of three)
    auto middle = (left + right) / 2;
    vector<int> three{arr[left], arr[middle], arr[right]};
    sort(three.begin(), three.end(), greater());
    arr[left] = three[0];
    arr[middle] = three[1];
    arr[right] = three[2];
    auto pivot = middle;

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
            pivot = lp;
            break;
        } else
            swap(arr[lp], arr[rp]);
    }

    // pivot is larger than k - 1 numbers
    if (pivot == k - 1) return arr[pivot];
    // the number of numbers pivot greater than is less than k - 1
    else if (pivot < k - 1)
        return partition(arr, pivot + 1, right, k);
    // the number of number pivot greater than is more than k - 1
    else
        return partition(arr, left, pivot - 1, k);

    return -1;
}

auto main() -> int {
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    int seq_len, k;
    cin >> seq_len >> k;

    vector<int> arr(seq_len);

    for (int tmp, i = 0; i < seq_len; i++) {
        cin >> tmp;
        arr[i] = tmp;
    }

    for (int i = k; i <= seq_len; i++) {
        vector<int> tmp_arr(arr.begin(), arr.begin() + i);
        cout << partition(tmp_arr, 0, tmp_arr.size() - 1, k) << "\n";
    }

    return 0;
}