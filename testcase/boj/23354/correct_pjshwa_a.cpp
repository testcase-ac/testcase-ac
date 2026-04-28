#include<bits/stdc++.h>
#define int ll
#define sz(x) int((x).size())
#define all(x) (x).begin(),(x).end()
using namespace std;
using ll = long long;
using pi = pair<int, int>;
const int inf = 0x3f3f3f3f3f3f3f3f;
const int minf = 0xc0c0c0c0c0c0c0c0;
 
const int dx[] = { -1,0,0,1 };
const int dy[] = { 0,-1,1,0 };
 
 
int A[1010][1010];
int dist[15][1010][1010];
int dp[1 << 12][12];
 
signed main() {
    ios::sync_with_stdio(0); cin.tie(0);
 
 
    int n; cin >> n;
 
    vector<pi> v(1, pi(-1, -1));
 
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> A[i][j];
            if (A[i][j] == 0) {
                v.emplace_back(i, j);
            }
            else if (A[i][j] == -1) {
                v[0] = pi(i, j);
            }
        }
    }
 
    if (sz(v) == 1) {
        cout << 0 << '\n';
        return 0;
    }
 
    assert(v[0].first != -1);
 
    memset(dist, 0x3f, sizeof(dist));
 
    using Z = pair<int, pi>;
 
    for (int i = 0; i < sz(v); i++) {
        auto [x, y] = v[i];
 
        priority_queue<Z, vector<Z>, greater<Z>> pq;
 
        dist[i][x][y] = 0;
 
        pq.emplace(0, pi(x, y));
 
        while (sz(pq)) {
            auto [curd, cur] = pq.top(); pq.pop();
            auto [x, y] = cur;
 
            if (dist[i][x][y] != curd) {
                continue;
            }
 
            for (int k = 0; k < 4; k++) {
                int nx = x + dx[k], ny = y + dy[k];
                if (nx >= 1 && nx <= n && ny >= 1 && ny <= n) {
                    if (dist[i][nx][ny] > curd + (A[nx][ny] <= 0 ? 0 : A[nx][ny])) {
                        dist[i][nx][ny] = curd + (A[nx][ny] <= 0 ? 0 : A[nx][ny]);
                        pq.emplace(dist[i][nx][ny], pi(nx, ny));
                    }
                }
            }
        }
    }
 
    memset(dp, 0x3f, sizeof(dp));
 
    dp[1][0] = 0;
 
    int sz = sz(v);
 
    for (int bit = 1; bit < 1 << sz; bit++) {
        for (int i = 0; i < sz(v); i++) {
            if (dp[bit][i] == inf) {
                continue;
            }
 
            for (int j = 0; j < sz(v); j++) {
                if (i == j) {
                    continue;
                }
 
                auto [x, y] = v[j];
 
                if (dp[bit | 1 << j][j] > dp[bit][i] + dist[i][x][y]) {
                    dp[bit | 1 << j][j] = dp[bit][i] + dist[i][x][y];
                }
            }
        }
    }
 
    int res = inf;
 
    for (int i = 1; i < sz; i++) {
        res = min(res, dp[(1 << sz) - 1][i] + dist[i][v[0].first][v[0].second]);
    }
 
    assert(res != inf);
 
 
    cout << res << '\n';
 
 
 
 
 
    return 0;
}