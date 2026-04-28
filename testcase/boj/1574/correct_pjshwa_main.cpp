#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 300;
int R, C, ma[MAXN], mb[MAXN], B[MAXN][MAXN];
bool vis[MAXN];

bool dfs(int a) {
  vis[a] = true;
  for (int b = 0; b < C; ++b) {
    if (B[a][b] == 1) continue;
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void solve() {
  int N; cin >> R >> C >> N;
  for (int i = 0; i < N; ++i) {
    int r, c; cin >> r >> c;
    B[r - 1][c - 1] = 1;
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < R; i++) {
    if (ma[i] != -1) continue;
    fill(vis, vis + R, false);
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
