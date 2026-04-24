#include <bits/stdc++.h>
using namespace std;
int arr[50][50];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> ones;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 1) {
                ones.push_back({i, j});
            }
        }
    }
    int ans = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            int min_dist = 10000;
            for(auto [x, y]: ones) {
                min_dist = min(min_dist, max(abs(x-i), abs(y-j)));
            }
            ans = max(ans, min_dist);
        }
    }
    cout << ans << endl;
}
