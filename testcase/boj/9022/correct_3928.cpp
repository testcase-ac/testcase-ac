#include <bits/stdc++.h>
#define int long long
using namespace std;
struct point {
    int x, y;
    bool operator<(const point &p) const {
        return x + abs(y) < p.x + abs(p.y);
    }
};
int lft_land(point p) {
    return p.x - abs(p.y);
}
int rht_land(point p) {
    return p.x + abs(p.y);
}
const int MX = 1e4+1;
void solve() {
    int N;
    cin >> N;
    vector<point> arr(N+1);
    vector<int> dp(N+1, LLONG_MAX);
    for(int i=1; i<=N; i++) {
        cin >> arr[i].x >> arr[i].y;
    }
    sort(arr.begin()+1, arr.end());
    int mn = N;
    for(int t=N; t>=1; t--) {
        if(lft_land(arr[t]) < lft_land(arr[mn])) {
            mn = t;
        }
        for(int i=mn, j=mn; i<=N; i=j) {
            while(j <= N && !(arr[i] < arr[j])) {
                j++;
            }
            int sz = rht_land(arr[i]) - lft_land(arr[mn]);
            int cur =  sz * sz + (j <= N ? dp[j] : 0);
            if(cur < dp[t]) {
                dp[t] = cur;
            }
        }
    }

    cout << fixed << setprecision(1) << (1.l * dp[1] / 2) << '\n';
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        solve();
    }
}
