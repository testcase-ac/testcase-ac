#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXT = 100;
vector<int> adj[MAXN + 1];
int ma[MAXN + 1], mb[MAXN + 1];
bool vis[MAXN + 1];

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
  int N, M; cin >> N >> M;

  for (int i = 1; i <= MAXT; ++i) adj[i].clear();
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 1; i <= M; ++i) {
    int t1, t2, a, x; cin >> t1 >> t2 >> a;
    while (a--) {
      cin >> x;
      for (int j = t1 + 1; j <= t2; ++j) adj[j].push_back(x);
    }
  }

  int match = 0;
  for (int i = 1; i <= MAXT; ++i) {
    if (ma[i] != -1) continue;
    memset(vis, false, sizeof vis);
    if (dfs(i) && ++match == N) return cout << i << '\n', void();
  }
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
