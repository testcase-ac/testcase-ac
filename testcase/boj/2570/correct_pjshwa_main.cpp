#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
vector<int> adj[MAXN * MAXN];
int ma[MAXN * MAXN], mb[MAXN * MAXN], B[MAXN][MAXN], S[MAXN][MAXN];
bool vis[MAXN * MAXN];

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
  while (M--) {
    int x, y; cin >> x >> y; --x; --y;
    B[x][y] = 1;
  }

  auto oob = [&](int x, int y) {
    return x < 0 || x >= N || y < 0 || y >= N;
  };

  int it = 0;
  for (int i = 0; i < 2 * N; ++i) for (int j = 0; j < N; ++j) {
    int x = i - j, y = j;
    if (oob(x, y) || B[x][y]) continue;

    int px = i - j + 1, py = j - 1;
    if (oob(px, py) || B[px][py]) ++it;
    S[x][y] = it;
  }

  it = 0;
  for (int i = N; i >= -N; --i) for (int j = 0; j < N; ++j) {
    int x = i + j, y = j;
    if (oob(x, y) || B[x][y]) continue;

    int px = i + j - 1, py = j - 1;
    if (oob(px, py) || B[px][py]) ++it;
    adj[it].push_back(S[x][y]);
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 1; i <= it; ++i) {
    if (ma[i] != -1) continue;
    fill(vis, vis + it + 1, false);
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
