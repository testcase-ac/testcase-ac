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
    int cur = 0;
    int ans = 0;
    for(int i = n - 1; i >= 0; i--) {
        if(v[i] > cur) {
            ans++;
            cur = v[i];
        }
    }
    cout << ans;
}
