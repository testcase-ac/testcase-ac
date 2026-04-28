#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
vector<int> graph[MAX + 1], linvs[MAX + 1];
int lcnt[MAX + 1], maxl;

void dfs(int v, int p, int l) {
  lcnt[l]++;
  maxl = max(maxl, l);
  for (int d : graph[v]) {
    if (d != p) dfs(d, v, l + 1);
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  ll ans = 0;
  for (int i = 1; i <= n; i++) {

    for (int d : graph[i]) {
      maxl = 0, dfs(d, i, 1);
      for (int l = 1; l <= maxl; l++) {
        linvs[l].push_back(lcnt[l]);
        lcnt[l] = 0;
      }
    }

    for (int j = 1; j <= n; j++) {
      ll head = 0, tail = accumulate(linvs[j].begin(), linvs[j].end(), 0LL);
      for (int e : linvs[j]) {
        tail -= e;
        ans += (ll)e * head * tail;
        head += e;
      }
      linvs[j].clear();
    }

  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
