#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, k;
    cin >> n >> k;
    vector<int> v(n);
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    multiset<int> ms;
    for(int i = 1; i < n - k - 1; i++) {
        ms.insert(v[i] - v[i - 1]);
    }
    int ans = INT_MAX;
    for(int l = 0;; l++) {
        int r = l + (n - k);
        if(r > n) {
            break;
        }
        int mx = v[r - 1] - v[l];
        ms.insert(v[r - 1] - v[r - 2]);
        ans = min(ans, mx + *ms.begin());
        ms.erase(ms.find(v[l + 1] - v[l]));
    }
    cout << ans;
}
