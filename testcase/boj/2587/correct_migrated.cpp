#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a=0;
    int r[5];
    for(int i=0;i<5;i++) {
        cin >> r[i];
        a+=r[i];
    } sort(r,r+5);
    cout << a/5 << endl << r[2];
}
