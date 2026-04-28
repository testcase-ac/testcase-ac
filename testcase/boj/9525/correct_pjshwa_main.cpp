#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
vector<int> adj[MAXN * MAXN + 1];
int ma[MAXN * MAXN + 1], mb[MAXN * MAXN + 1];
bool vis[MAXN * MAXN + 1];
char board[MAXN + 1][MAXN + 1];
int Ri[MAXN][MAXN], Ci[MAXN][MAXN];

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
  int N, ri = 0, ci = 0; cin >> N;
  for (int i = 0; i < N; ++i) cin >> board[i];
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (board[i][j] == 'X') continue;
    if (j == 0 || board[i][j - 1] == 'X') ++ri;
    Ri[i][j] = ri;
  }
  for (int j = 0; j < N; ++j) for (int i = 0; i < N; ++i) {
    if (board[i][j] == 'X') continue;
    if (i == 0 || board[i - 1][j] == 'X') ++ci;
    Ci[i][j] = ci;
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (board[i][j] == 'X') continue;
    adj[Ri[i][j]].push_back(Ci[i][j]);
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 1; i <= ri; i++) {
    if (ma[i] != -1) continue;
    fill(vis, vis + ri + 1, false);
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
