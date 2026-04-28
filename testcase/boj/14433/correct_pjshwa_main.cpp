#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 300;
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

void init(int N) {
  for (int i = 0; i < N; ++i) {
    adj[i].clear();
    ma[i] = mb[i] = -1;
  }
}

void solve() {
  int N, M, K1, K2; cin >> N >> M >> K1 >> K2;

  init(N);
  while (K1--) {
    int i, j; cin >> i >> j;
    adj[i - 1].push_back(j - 1);
  }

  int match1 = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; i++) {
    if (ma[i] != -1) continue;
    fill(vis, vis + N, false);
    if (dfs(i)) ++match1;
  }

  init(N);
  while (K2--) {
    int i, j; cin >> i >> j;
    adj[i - 1].push_back(j - 1);
  }

  int match2 = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; i++) {
    if (ma[i] != -1) continue;
    fill(vis, vis + N, false);
    if (dfs(i)) ++match2;
  }

  if (match1 < match2) cout << "네 다음 힐딱이\n";
  else cout << "그만 알아보자\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
