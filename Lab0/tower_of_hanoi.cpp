#include <iostream>
#include <cmath>

using namespace std;

void honai(int, int, int, int);

int main(void){
    int num_of_disk;

    // Read Input
    cin >> num_of_disk;

    // Output less movement
    cout << pow(2, num_of_disk) - 1 << "\n";

    // Output movement
    honai(num_of_disk, 1, 2, 3);
}

void honai(int n, int start, int aux, int dest){
    if(n == 0) return;
    
    // Move n - 1 disks from start_rod to aux_rod and move largest disk to dest_rod
    honai(n - 1, start, dest, aux);
    cout << start << " " << dest << "\n";

    // Move n - 1 disks from aux_rod to dest_rod
    honai(n - 1, aux, start, dest);
}