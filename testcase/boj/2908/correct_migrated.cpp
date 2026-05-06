#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    string a,b;
    cin >> a >> b;
    for(int i=0;i<(a.size()+1)/2;i++) {
        swap(a[i],a[a.size()-i-1]);
    } for(int i=0;i<(b.size()+1)/2;i++) {
        swap(b[i],b[b.size()-i-1]);
    } if(stoi(a)>stoi(b)) {
        cout << a;
    } else {
        cout <<b;
    }
    return 0;
}
