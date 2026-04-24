#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    string code;
    cin >> code;
    int t;
    cin >> t;
    int cnt = 0;
    while(t--) {
        string x;
        cin >> x;
        if(code.substr(0, 5) == x.substr(0, 5)) {
            cnt++;
        }
    }
    cout << cnt;
}
