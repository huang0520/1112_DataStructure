#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void){
    int bridge_num;
    vector <pair<int, int> > bridge_height;

    // Read Input (index, height)
    cin >> bridge_num;
    for(int i = 1; i <= bridge_num; i++){
        int tmp;
        cin >> tmp;
        bridge_height.push_back(make_pair(i, tmp));
    }

    // According to the height, sort the data
    sort(bridge_height.begin(), bridge_height.end(), 
         [] (pair<int, int> &a, pair<int, int> &b) {return (a.second > b.second);});

    // Output the index of the heightest bridge
    cout << bridge_height.front().first;
}