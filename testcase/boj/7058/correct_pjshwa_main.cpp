#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 205, MAXL = 50000;
int A[MAXN][MAXN], C[MAXN][MAXN];
vector<int> graph[MAXL];
int ma[MAXL], mb[MAXL], inv_X[MAXL], inv_Y[MAXL];
bool vis[MAXL];

bool dfs(int a) {
  vis[a] = true;
  for (int b : graph[a]) {
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) cin >> A[i][j];

  int cj = -1;
  memset(C, -1, sizeof(C));
  for (int j = 0; j < M; ++j) for (int i = 0; i < N; ++i) {
    if (A[i][j] == 2) continue;
    if (i == 0 || A[i - 1][j] == 2) ++cj;
    C[i][j] = cj; inv_Y[cj] = j;
  }

  int ci = -1;
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (A[i][j] == 2) continue;
    if (j == 0 || A[i][j - 1] == 2) ++ci;
    if (A[i][j] == 0) graph[ci].push_back(C[i][j]);
    inv_X[ci] = i;
  }

  int Sz = ci + 2, Tz = cj + 2;
  fill(ma, ma + Sz, -1);
  fill(mb, mb + Tz, -1);

  for (int i = 0; i < Sz; i++) {
    if (ma[i] != -1) continue;
    fill(vis, vis + Tz, false);
    dfs(i);
  }

  vector<pii> matches;
  for (int i = 0; i < Sz; ++i) {
    if (ma[i] != -1) matches.emplace_back(i, ma[i]);
  }

  cout << matches.size() << '\n';
  for (auto& [i, j] : matches) cout << inv_X[i] + 1 << ' ' << inv_Y[j] + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
