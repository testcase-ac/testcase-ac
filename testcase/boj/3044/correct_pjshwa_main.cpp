#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000, MOD = 1e9;
vector<int> gf[MAX + 1], gb[MAX + 1];
bool visf[MAX + 1], visb[MAX + 1], cyc[MAX + 1];
bool m = false;
int d[MAX + 1], vis[MAX + 1];

int r(int v) {
  if (d[v] != -1) return d[v];
  if (v == 2) return d[v] = 1;

  int ret = 0;
  for (int u : gf[v]) {
    if (!visb[u]) continue;

    ret = (ret + r(u));
    if (ret >= MOD) {
      ret -= MOD;
      m = true;
    }
  }
  return d[v] = ret;
}

void dfsf(int v) {
  visf[v] = true;
  for (int u : gf[v]) {
    if (visf[u]) continue;
    dfsf(u);
  }
}

void dfsb(int v) {
  visb[v] = true;
  for (int u : gb[v]) {
    if (visb[u]) continue;
    dfsb(u);
  }
}

bool is_cyclic(int v) {
  if (vis[v] == -1) return true;
  if (vis[v] == 1) return false;

  vis[v] = -1;
  for (int u : gf[v]) {
    if (visb[u]) {
      if (is_cyclic(u)) return true;
    }
  }
  vis[v] = 1;
  return false;
}

void solve() {
  int N, M;
  cin >> N >> M;
  while (M--) {
    int u, v;
    cin >> u >> v;
    gf[u].push_back(v);
    gb[v].push_back(u);
  }
  dfsf(1);
  dfsb(2);

  for (int i = 1; i <= N; i++) {
    if (visf[i] && visb[i]) {
      if (is_cyclic(i)) return cout << "inf\n", void();
    }
  }

  memset(d, -1, sizeof(d));
  int ans = r(1);

  if (m) {
    string ans_s = to_string(ans);
    while (ans_s.size() < 9) ans_s = "0" + ans_s;
    cout << ans_s << '\n';
  }
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
