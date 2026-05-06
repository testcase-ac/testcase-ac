#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int a,b,c;
    cin >> a >> b;
    int r[a];
    for(int i=0;i<a;i++) {
        cin >> r[i];
    } sort(r,r+a);
    cout << r[a-b];
}
