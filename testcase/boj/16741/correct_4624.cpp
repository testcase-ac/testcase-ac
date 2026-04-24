#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int R, S, P;
    cin >> R >> S >> P;
    vector<int> arr;
    for(int t=0; t<P; t++) {
        int i, j;
        cin >> i >> j;
        int dist = (j <= S ? S + 1 - j : j - S) + (R + 1 - i);
        arr.push_back(dist);
    }
    sort(arr.begin(), arr.end());
    int ans = 0;
    for(int t: arr) {
        ans++;
        ans = max(ans, t);
    }
    cout << ans;
}
