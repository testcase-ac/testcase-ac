#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
vector<int> adj[MAXN];
int ma[MAXN], mb[MAXN], A[MAXN];
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
  for (int i = 1; i <= N; ++i) {
    int k; cin >> k;
    while (k--) {
      int v; cin >> v;
      adj[i - 1].push_back(v - 1);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; ++i) {
    if (ma[i] != -1) continue;
    memset(vis, false, sizeof vis);
    if (dfs(i)) ++match;
  }

  set<int> uA, uB;
  for (int i = 0; i < N; ++i) {
    cout << "i = " << i << ", ma[i] = " << ma[i] << '\n';
    // if (ma[i] != -1) uA.insert(i), uB.insert(ma[i]);
  }
  // for (int i = 0; i < M; ++i) {
  //   if (mb[i] != -1) uB.insert(i);
  // }

  cout << match << '\n';
  cout << uA.size() << ' ';
  for (int u : uA) cout << u + 1 << ' ';
  cout << '\n';
  cout << uB.size() << ' ';
  for (int u : uB) cout << u + 1 << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
