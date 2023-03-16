#include <iostream>
#include <climits>

#define lli long long int

using namespace std;

int main(void){
    // ios optimization
    ios::sync_with_stdio(false);
    cin.tie(0);

    lli n, total = 0, ans = INT_MAX;

    // Read apple number
    cin >> n;

    lli weight[n];

    for (int i = 0; i < n; i++){
        cin >> weight[i];
        total += weight[i];
    }

    for (int i = 0; i < 1 << n; i++){
        lli tmp = 0;
        for (int j = 0; j < n; j++){
            if (i & 1 << j) tmp += weight[j];
        }
        lli curr = abs(total - tmp - tmp);
        ans = min(ans, curr);
    }
    cout << ans << "\n";
}