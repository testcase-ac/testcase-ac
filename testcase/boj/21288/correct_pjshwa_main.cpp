#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 13;
vector<int> adj[MAXN];
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
  int N, K, M; cin >> N >> K >> M;

  vector<string> D(N);
  for (auto& s : D) cin >> s;

  int ans = 0;
  while (M--) {
    for (int i = 0; i < N; ++i) adj[i].clear();

    string T; cin >> T;
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
      int ok = 0;
      for (char c : D[i]) ok |= (c == T[j]);
      if (ok) adj[i].push_back(j);
    }

    int match = 0;
    memset(ma, -1, sizeof ma);
    memset(mb, -1, sizeof mb);

    for (int i = 0; i < N; ++i) {
      if (ma[i] != -1) continue;
      memset(vis, false, sizeof vis);
      if (dfs(i)) ++match;
    }
    ans += match == N;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
