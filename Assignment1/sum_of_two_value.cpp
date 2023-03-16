#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(void){
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    int size, target, check = 0;
    vector <pair <int, int>> arr;

    // Read input
    cin >> size >> target;

    arr.reserve(size);

    for (int i = 1, input; cin >> input; i++) arr.emplace_back(input, i);

    sort(arr.begin(), arr.end());

    for (int l = 0, r = arr.size() - 1; l < r && check == 0; ) {
        int got = arr[l].first + arr[r].first;
        
        if (got == target) {
            cout << arr[l].second << ' ' << arr[r].second << '\n';
            check = 1;
        }
        else if (got < target) l++;
        else r--;
    }

    if (check == 0) cout << "IMPOSSIBLE\n";
}