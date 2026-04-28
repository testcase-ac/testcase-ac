#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXL = 600, MAXN = 360'000;
const int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
char board[MAXL + 1][MAXL + 1];
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

int tc;
void solve() {
  cout << "Case " << ++tc << ": ";

  int L; cin >> L;
  for (int i = 0; i < L; ++i) cin >> board[i];

  int N = 0;
  for (int i = 0; i < L; ++i) for (int j = 0; j < L; ++j) {
    if ((i + j) % 2 == 0) continue;
    if (board[i][j] == '#') ++N;
  }
  for (int i = 0; i < N; ++i) adj[i].clear();

  int Ni = 0;
  for (int i = 0; i < L; ++i) for (int j = 0; j < L; ++j) {
    if ((i + j) % 2 == 0) continue;
    if (board[i][j] == '.') continue;
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= L || nj < 0 || nj >= L) continue;
      if (board[ni][nj] == '#') adj[Ni].push_back(ni * L + nj);
    }
    ++Ni;
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
  cin >> t;
  while (t--) solve();
}
