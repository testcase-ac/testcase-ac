#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
int from[MAX + 1];
bool vis[MAX + 1];

void bfs(int s) {
  memset(vis, 0, sizeof vis);
  vis[s] = 1;
  queue<int> q;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v : graph[u]) {
      if (!vis[v]) {
        vis[v] = 1;
        q.push(v);
        from[v] = u;
      }
    }
  }
}

void solve() {
  int n, s, c, h, e;
  cin >> n >> s >> c >> h;
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    cin >> a >> b;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  vector<int> fwd, bwd;

  bfs(s);
  e = c;
  while (e != s) {
    fwd.push_back(e);
    e = from[e];
  }
  fwd.push_back(s);
  reverse(fwd.begin(), fwd.end());

  bfs(c);
  e = h;
  while (e != c) {
    bwd.push_back(e);
    e = from[e];
  }
  reverse(bwd.begin(), bwd.end());
  for (int el : bwd) fwd.push_back(el);

  int sz = fwd.size();
  int vis[MAX + 1];
  memset(vis, -1, sizeof vis);

  // Each number occurs at most twice
  ll ans = 0, dec = 0;
  for (int i = 0; i < sz; i++) {
    if (vis[fwd[i]] != -1) {
      ans += (i - vis[fwd[i]]);
      dec++;
    }
    else ans += i;
    ans -= dec;
    vis[fwd[i]] = i;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
