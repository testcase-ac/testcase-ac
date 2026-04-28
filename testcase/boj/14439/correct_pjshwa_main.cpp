#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 40;
char board[MAXN + 1][MAXN + 1];
vector<int> adj[MAXN];
int ma[MAXN], mb[MAXN];
bool vis[MAXN], Af[MAXN], Bf[MAXN];

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
  int N, A, B; cin >> N >> A >> B; --A; --B;
  for (int i = 0; i < N; ++i) cin >> board[i];

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    if (i == A || i == B) continue;
    if (board[A][i] == 'Y' && board[B][i] == 'Y') {
      ++ans;
      for (int j = 0; j < N; ++j) board[i][j] = board[j][i] = 'N';
    }
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (board[A][i] == 'Y' && board[B][j] == 'Y' && board[i][j] == 'Y') {
      adj[i].push_back(j);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; ++i) {
    if (ma[i] != -1) continue;
    fill(vis, vis + N, false);
    if (dfs(i)) ++match;
  }
  cout << ans + match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
