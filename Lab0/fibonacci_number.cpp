#include <iostream>
#include <cmath>

using namespace std;

int fib(int&);
int mod(int);

int main(void){
    int n;
    cin >> n;

    cout << mod(fib(n)) << "\n";
}

int fib(int &n){
    if(n == 0) return 0;

    int f = 0, s = 1;
    for(int i = 1; i < n; i++){
        int tmp;
        tmp = f;
        f = s;
        s = mod(f) + mod(tmp);
    }
    return s;
}

int mod(int num){
    return (num % ((int) pow(10, 9) + 7));
}