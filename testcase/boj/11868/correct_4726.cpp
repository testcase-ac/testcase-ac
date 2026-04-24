#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int ans = 0;
    for(int i = 0; i < n; i++) {
        ans ^= v[i];
    }
    if(ans) {
        cout << "koosaga" << endl;
    } else {
        cout << "cubelover" << endl;
    }
}
