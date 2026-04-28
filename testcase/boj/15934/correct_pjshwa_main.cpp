#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 50, INF = 1e18;
vector<int> adj[MAXN * MAXN];
int ma[MAXN], mb[MAXN], B[MAXN][MAXN];
int R, C;
bool vis[MAXN];

void compress(vector<int>& v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

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

bool check(int Z) {

}

void solve() {
  int D, W; cin >> R >> C >> D >> W;

  vector<int> ys;
  for (int i = 0; i < R; ++i) for (int j = 0; j < C; ++j) {
    cin >> B[i][j];
    ys.push_back(B[i][j]);
  }
  compress(ys);

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; i++) {
    if (ma[i] != -1) continue;
    memset(vis, false, sizeof vis);
    if (dfs(i)) ++match;
  }
  cout << N + M - match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
