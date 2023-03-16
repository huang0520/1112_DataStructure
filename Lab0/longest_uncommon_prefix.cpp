#include <iostream>
#include <string>

using namespace std;

int main(void){
    int str_leng;
    string str;

    // Read Input
    cin >> str_leng
        >> str;

    // Check whether char n is same as char n+i
    for(int i = 1; i < str_leng; i++){
        int l = 0;
        for(auto itr = str.begin(); itr + i != str.end(); itr++){
            if(*itr == *(itr + i)) break;
            l++;
        }
        cout << l << "\n";
    }
}