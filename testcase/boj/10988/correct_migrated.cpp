#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    string a,b;
    cin >> a;
    b=a;
    for(int i=0;i<(a.size()+1)/2;i++) {
        swap(a[i],a[a.size()-i-1]);
    }
    if(a==b) {
        cout << '1';
    } else {
        cout << '0';
    }
    return 0;
}
