#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void search(vector <long long>&, long long&);

int main(void){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int array_len, query_len;
    vector <long long> array, query;

    // Read Input
    cin >> array_len >> query_len;

    array.reserve(array_len);
    query.reserve(query_len);

    for(int i = 0; i < array_len; i++){
        long long tmp;
        cin >> tmp;
        array.push_back(tmp);
    }

    for(int i = 0; i < query_len; i++){
        long long tmp;
        cin >> tmp;
        query.push_back(tmp);
    }

    sort(array.begin(), array.end());

    for(auto itr : query){
        search(array, itr);
        if (query.size() > 1) cout << " ";
    }
}

void search(vector <long long> &array, long long &target){
    int left = 0;
    int right = array.size() - 1;
    int middle;

    while(left <= right){
        middle = (left + right) / 2;
        if(target > array[middle]) left = middle + 1;
        else if(target < array[middle]) right = middle - 1;
        else {
            cout << "Y";
            return;
        }
    }

    cout << "N";
}