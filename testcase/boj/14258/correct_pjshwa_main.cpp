#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int board[MAX][MAX];
int parent[MAX * MAX + 1];
int vals[MAX * MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void solve() {
  int n, m;
  cin >> n >> m;

  priority_queue<tuple<int, int, int>> pq;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    int x;
    cin >> x;
    pq.push({x, i, j});
  }

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) parent[i * m + j] = i * m + j;

  ll tsum = 0, ans = 0;
  while (!pq.empty()) {
    auto [v, i, j] = pq.top();
    pq.pop();

    set<int> sides;
    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= n || nj < 0 || nj >= m) continue;
      if (board[ni][nj] == 0) continue;
      sides.insert(Find(ni * m + nj));
    }

    int nval = v;
    for (int side : sides) {
      nval ^= vals[side];
      tsum -= vals[side];
      Union(i * m + j, side);
    }

    board[i][j] = v;
    vals[Find(i * m + j)] = nval;
    tsum += nval;
    ans = max(ans, tsum);
  }

  cout << ans << '\n';


}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
