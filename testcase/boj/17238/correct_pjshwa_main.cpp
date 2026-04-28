#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
vector<int> adj[MAXN];
int C[MAXN], D[MAXN];
int ma[MAXN], mb[MAXN];
bool vis[MAXN];

bool dfs(int a) {
  vis[a] = true;
  for (int b : adj[a]) {
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> C[i];
  for (int i = 0; i < N; ++i) cin >> D[i];

  ll l = 0, r = 2e9 + 1;
  while (l < r) {
    ll m = (l + r) / 2;
    for (int i = 0; i < N; ++i) {
      adj[i].clear();
      ma[i] = mb[i] = -1;
    }
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
      if ((C[i] ^ D[j]) >= m) adj[i].push_back(j);
    }

    int match = 0;
    for (int i = 0; i < N; ++i) {
      if (ma[i] != -1) continue;
      memset(vis, false, sizeof vis);
      if (dfs(i)) ++match;
    }

    if (match == N) l = m + 1;
    else r = m;
  }
  cout << l - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
