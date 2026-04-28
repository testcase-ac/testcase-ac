#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
set<pii> graph[MAX + 1];
int ssize[MAX + 1], osize[MAX + 1];
ll d[10'001];

void dfs(int u, int val) {
  ll addend = 0;
  for (auto [nval, v] : graph[u]) {
    dfs(v, nval);
    addend += (ll)ssize[u] * ssize[v];
    ssize[u] += ssize[v];
  }
  ssize[u] += osize[u];
  d[val] += addend;
}

void solve() {
  int n, q;
  cin >> n >> q;

  int s, x, ni = 0;
  for (int i = 0; i < n; i++) {
    cin >> x;

    s = 0;
    for (int j = 0; j < x; j++) {
      int y;
      cin >> y;

      auto it = graph[s].lower_bound({y, 0});
      if (it->first == y) s = it->second;
      else {
        graph[s].insert({y, ++ni});
        s = ni;
      }
    }
    osize[s]++;
  }
  dfs(0, 0);

  while (q--) {
    int x;
    cin >> x;
    cout << d[x] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
