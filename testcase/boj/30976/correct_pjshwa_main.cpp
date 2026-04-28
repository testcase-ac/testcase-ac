#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 400;
vector<int> adj[MAXN];
int ma[MAXN], mb[MAXN], G[MAXN], B[MAXN], L[MAXN], U[MAXN];
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
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> G[i];
  for (int i = 0; i < M; ++i) cin >> B[i];
  for (int i = 0; i < N; ++i) cin >> L[i];
  for (int i = 0; i < M; ++i) cin >> U[i];

  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (B[j] < L[i] && G[i] > U[j]) adj[i].push_back(j);
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; i++) {
    if (ma[i] != -1) continue;
    fill(vis, vis + N, false);
    if (dfs(i)) ++match;
  }
  cout << match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
