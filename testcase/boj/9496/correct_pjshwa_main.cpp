#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50;
vector<int> adj[MAXN];
int ma[MAXN], mb[MAXN];
bool vis[MAXN];
char B[MAXN + 1][MAXN + 1];

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
  int N, C[4]{}; string Gs; cin >> N >> Gs;

  vector<int> G;
  for (char c : Gs) G.push_back(c - '0');
  for (int i = 0; i < N; ++i) ++C[G[i]];
  for (int i = 0; i < N; ++i) cin >> B[i];

  function<int(int, int)> get_max_match = [&](int t1, int t2) {
    for (int i = 0; i < N; ++i) adj[i].clear();
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
      if (B[i][j] == 'N') continue;
      if (G[i] != t1 || G[j] != t2) continue;
      adj[i].push_back(j);
    }

    int match = 0;
    memset(ma, -1, sizeof ma);
    memset(mb, -1, sizeof mb);

    for (int i = 0; i < N; ++i) {
      if (ma[i] != -1) continue;
      memset(vis, false, sizeof vis);
      if (dfs(i)) ++match;
    }
    return N - match;
  };

  int ans = max({
    get_max_match(1, 2),
    get_max_match(1, 3),
    get_max_match(2, 3)
  });
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
