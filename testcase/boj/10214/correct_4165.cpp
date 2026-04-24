#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve() {
    int a = 0, b = 0;
    for(int i = 0; i < 9; i++) {
        int x, y;
        cin >> x >> y;
        a += x;
        b += y;
    }
    if(a > b) {
        cout << "Yonsei\n";
    } else if(a < b) {
        cout << "Korea\n";
    } else {
        cout << "Draw\n";
    }
}
int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin >> t;
    while(t--) {
        solve();
    }
}
