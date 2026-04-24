#include <bits/stdc++.h>
using namespace std;
#define int long long

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int N;
    cin >> N;

    vector<pair<int, int>> v(N);
    int sx = 0, sy = 0;

    for(int i=0; i<N; i++) {
        cin >> v[i].first >> v[i].second;
        sx += v[i].first;
        sy += v[i].second;
    }
    cout << sx << " " << sy << "\n";
    int ans = INT_MAX;
    for(int i=0; i<N; i++) {
        int dx = sx - v[i].first;
        int dy = sy - v[i].second;
        ans = min(ans, dx * dx + dy * dy);
    }
    cout << fixed << setprecision(2) << sqrt(ans);
}
