#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
const ll INF = 1e14;
int n, a, b, c;
ll cdist[MAX][MAX];

void dijk(int si, int sj) {
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cdist[i][j] = INF;
  cdist[si][sj] = 0;

  priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> pq;
  pq.push({0, si, sj});

  while (!pq.empty()) {
    auto [wi, ui, uj] = pq.top();
    pq.pop();

    if (wi > cdist[ui][uj]) continue;
    
    for (int k = 0; k < 8; k++) {
      int nx = ui + dx[k], ny = uj + dy[k];
      if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
      ll mdist = wi + a;
      if (cdist[nx][ny] > mdist) {
        cdist[nx][ny] = mdist;
        pq.push({mdist, nx, ny});
      }
    }

    for (int k = -n; k <= n; k++) {
      int nx = ui - k, ny = uj + k;
      if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
      ll mdist = wi + b;
      if (cdist[nx][ny] > mdist) {
        cdist[nx][ny] = mdist;
        pq.push({mdist, nx, ny});
      }
    }

    for (int k = -n; k <= n; k++) {
      int nx = ui + k, ny = uj + k;
      if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
      ll mdist = wi + b;
      if (cdist[nx][ny] > mdist) {
        cdist[nx][ny] = mdist;
        pq.push({mdist, nx, ny});
      }
    }

    for (int k = 0; k < n; k++) {
      ll mdist = wi + c;
      if (cdist[ui][k] > mdist) {
        cdist[ui][k] = mdist;
        pq.push({mdist, ui, k});
      }
      if (cdist[k][uj] > mdist) {
        cdist[k][uj] = mdist;
        pq.push({mdist, k, uj});
      }
    }
  }
}

void solve() {
  cin >> n >> a >> b >> c;

  vector<pii> u;
  int si, sj, m;
  cin >> si >> sj >> m;
  u.push_back({si, sj});
  for (int i = 0; i < m; i++) {
    int ui, uj;
    cin >> ui >> uj;
    u.push_back({ui, uj});
  }

  int uz = u.size();
  ll udist[5][5];
  for (int i = 0; i < uz; i++) {
    dijk(u[i].first, u[i].second);
    for (int j = 0; j < uz; j++) {
      auto [x, y] = u[j];
      udist[i][j] = cdist[x][y];
    }
  }

  int p[uz];
  for (int i = 0; i < uz; i++) p[i] = i;

  ll ans = INF;
  do {
    if (p[0] != 0) continue;

    ll cur = 0;
    for (int i = 0; i < uz - 1; i++) cur += udist[p[i]][p[i + 1]];
    ans = min(ans, cur);
  } while (next_permutation(p, p + uz));

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
