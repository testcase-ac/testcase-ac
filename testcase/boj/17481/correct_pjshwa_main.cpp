#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
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

void solve() {
  int N, M; cin >> N >> M;

  map<string, int> names;
  for (int i = 0; i < M; ++i) {
    string name; cin >> name;
    names[name] = i;
  }

  for (int i = 0; i < N; ++i) {
    int k; cin >> k;
    while (k--) {
      string name; cin >> name;
      adj[i].push_back(names[name]);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; i++) {
    if (ma[i] != -1) continue;
    memset(vis, false, sizeof vis);
    if (dfs(i)) ++match;
  }

  if (match == N) cout << "YES\n";
  else cout << "NO\n" << match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
