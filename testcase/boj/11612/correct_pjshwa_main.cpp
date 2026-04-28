#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
bool vis[MAX][2];
vector<int> graph[MAX];

void dfs(int v, int b) {
  vis[v][b] = 1;
  for (int u : graph[v]) {
    if (vis[u][1 - b]) continue;
    dfs(u, 1 - b);
  }
}

void solve() {
  int n;
  cin >> n;
  vector<tii> gears(n);

  int rs, re;
  for (int i = 0; i < n; i++) {
    int x, y, r;
    cin >> x >> y >> r;
    gears[i] = {x, y, r};

    if (i == 0) rs = r;
    if (i == n - 1) re = r;
  }

  int g = __gcd(rs, re);
  rs /= g, re /= g;

  for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
    auto [xi, yi, ri] = gears[i];
    auto [xj, yj, rj] = gears[j];
    
    int dx = abs(xi - xj), dy = abs(yi - yj);
    if (dx * dx + dy * dy == (ri + rj) * (ri + rj)) {
      graph[i].push_back(j);
      graph[j].push_back(i);
    }
  }

  dfs(0, 0);
  if (vis[n - 1][0]) {
    if (vis[n - 1][1]) cout << "The input gear cannot move.\n";
    else cout << rs << ':' << re << '\n';
  }
  else {
    if (vis[n - 1][1]) cout << '-' << rs << ':' << re << '\n';
    else cout << "The input gear is not connected to the output gear.\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
