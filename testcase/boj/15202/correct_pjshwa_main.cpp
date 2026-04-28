#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
vector<int> adj[MAXN], A[MAXN], B[MAXN];
string S;
int U[MAXN], lev[MAXN], par[MAXN], L = 0;

void dfs_pre(int v, int p, int c, int l = 0) {
  L += c; lev[v] = l;
  for (int u : adj[v]) {
    if (u == p) continue;
    par[u] = v;
    dfs_pre(u, v, 1 - c, l + 1);
  }
}

ll cur;
void dfs_c(int v, int p, int c) {
  for (int u : adj[v]) {
    if (u == p) continue;
    dfs_c(u, v, 1 - c);

    while (!A[u].empty() && !B[u].empty()) {
      int score_a = lev[A[u].back()] - lev[u];
      int score_b = lev[B[u].back()] - lev[u];
      cur += score_a + score_b;
      A[u].pop_back(); B[u].pop_back();
    }
  }

  if ((S[v] == 'B') ^ c) {
    if (c) A[v].push_back(v);
    else B[v].push_back(v);
  }

}

void solve() {
  int N; cin >> N >> S;
  memset(par, -1, sizeof(par));
  for (int i = 0; i < N - 1; ++i) {
    int u, v; cin >> u >> v; --u; --v;
    adj[u].push_back(v); adj[v].push_back(u);
  }

  int ac = 0;
  for (char c : S) ac += c == 'A';
  int bc = N - ac;

  dfs_pre(0, -1, 0); ll ans = -1;
  // if (L == ac) {
  //   cur = 0;
  //   dfs_c(0, -1, 1);

  //   if (ans == -1) ans = cur;
  //   else ans = min(ans, cur);
  // }

  if (L == bc) {
    cur = 0;
    dfs_c(0, -1, 0);

    if (ans == -1) ans = cur;
    else ans = min(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
