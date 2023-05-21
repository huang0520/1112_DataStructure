#include <cmath>
#include <iostream>

using namespace std;

auto mod(size_t x) -> size_t { return x % ((int)pow(10, 9) + 7); }

auto mod_exp(size_t base, size_t exp) -> size_t {
    if (exp == 0) return 1;
    if (exp == 1) return mod(base);

    size_t ans = 1;
    while (exp > 0) {
        if (exp & 1) ans = mod(ans * base);
        exp = exp >> 1;
        base = mod(base * base);
    }

    return ans;
}

auto main() -> int {
    size_t num_cal;
    cin >> num_cal;

    while (num_cal--) {
        size_t a, b;
        cin >> a >> b;
        cout << mod_exp(a, b) << "\n";
    }

    return 0;
}