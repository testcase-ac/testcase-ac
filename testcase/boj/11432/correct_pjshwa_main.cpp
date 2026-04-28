#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200;
vector<int> graph[MAXN + 1];
int ma[MAXN + 1], mb[MAXN + 1];
bool vis[MAXN + 1];

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

int tc;
void solve() {
  cout << "Data Set " << ++tc << ":\n";

  int M, N; cin >> M >> N;

  // init
  for (int i = 1; i <= N; ++i) graph[i].clear();
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 1; i <= N; ++i) {
    int s; cin >> s;
    for (int j = 0; j < s; ++j) {
      int si; cin >> si;
      graph[i].push_back(si);
    }
  }

  int match = 0;
  for (int i = 1; i <= N; ++i) {
    if (ma[i] != -1) continue;
    memset(vis, false, sizeof vis);
    if (dfs(i)) match++;
  }
  cout << match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) {
    solve();
    if (t) cout << '\n';
  }
}
