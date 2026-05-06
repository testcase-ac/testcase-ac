#include <iostream>
using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string t;
    int s,n;
    s=0;
    cin >> n;
    cin >> t;
    for(int i=0;i<n;i++) {
        s += t[i]-'0';
    }
    cout << s;
}
