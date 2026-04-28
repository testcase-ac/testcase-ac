#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
vector<int> adj[MAXN];
int color[MAXN];
int B[2], N;

void dfs(int v, int c) {
  color[v] = c;
  if (v < N) B[c - 1] += 1;

  for (int u : adj[v]) {
    if (color[u] == -1) {
      color[u] = c;
      dfs(u, 3 - c);
    }
    else if (color[u] == c) {
      cout << "-1\n";
      exit(0);
    }
  }
}

void solve() {
  cin >> N;
  map<int, int> Xt, Yt, Xc, Yc;
  for (int i = 0; i < 2 * N; ++i) {
    int x, y; cin >> x >> y;
    Xt[x] += 1; Yt[y] += 1;

    if (Xc.count(x)) {
      adj[Xc[x]].push_back(i); adj[i].push_back(Xc[x]);
    }
    else {
      Xc[x] = i;
    }
    if (Yc.count(y)) {
      adj[Yc[y]].push_back(i); adj[i].push_back(Yc[y]);
    }
    else {
      Yc[y] = i;
    }
  }

  for (int i = 1; i <= N; ++i) {
    if (Xt[i] != 2 || Yt[i] != 2) return cout << "-1\n", void();
  }

  memset(color, -1, sizeof(color)); int ans = 0;
  for (int i = 0; i < 2 * N; ++i) {
    if (color[i] != -1) continue;
    B[0] = B[1] = 0;
    dfs(i, 1);
    ans += min(B[0], B[1]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
