#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
vector<int> adj[MAXN + 1], dadj[MAXN + 1];
int indegree[MAXN + 1], mdepth[MAXN + 1], ans;

using T = tuple<int, int, int>;

// circle a contains circle b
bool contains(T& a, T& b) {
  ll ax, ay, ar, bx, by, br;
  tie(ax, ay, ar) = a; tie(bx, by, br) = b;
  if (ar < br) return false;
  return (ax - bx) * (ax - bx) + (ay - by) * (ay - by) <= (ar - br) * (ar - br);
}

void dfs(int v) {
  priority_queue<int, vector<int>, greater<int>> U;

  int cdepth = 0;
  for (int u : dadj[v]) {
    dfs(u);
    cdepth = max(cdepth, mdepth[u]);
    U.push(mdepth[u]);
    if (U.size() > 2) U.pop();
  }
  mdepth[v] = cdepth + 1;

  int cur = 0;
  while (!U.empty()) cur += U.top(), U.pop();
  ans = max(ans, cur);
}

void solve() {
  int N; cin >> N;

  vector<T> circles;
  for (int i = 0; i < N; ++i) {
    int x, y, r; cin >> x >> y >> r;
    circles.emplace_back(x, y, r);
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; j++) {
    if (i == j) continue;
    if (contains(circles[i], circles[j])) {
      adj[i + 1].push_back(j + 1);
      indegree[j + 1]++;
    }
  }

  queue<int> Q;
  for (int i = 1; i <= N; ++i) {
    if (indegree[i]) continue;
    Q.push(i);
    dadj[0].push_back(i);
  }

  while (!Q.empty()) {
    int v = Q.front(); Q.pop();
    for (int u : adj[v]) {
      if (--indegree[u] == 0) {
        Q.push(u);
        dadj[v].push_back(u);
      }
    }
  }

  ans = 0; dfs(0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
