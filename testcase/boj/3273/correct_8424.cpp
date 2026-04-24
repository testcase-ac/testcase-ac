#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    map<int, int> mp;
    for(int i = 0; i < n; i++) {
        int t;
        cin >> t;
        mp[t]++;
    }
    int x;
    cin >> x;
    int ans = 0;
    for(auto& [k, cnt]: mp) {
        auto val = mp[x - k];
        ans += cnt * val;
    }
    cout << ans / 2;
}
