#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 512;
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
  int N, M, K; cin >> N >> M >> K;

  vector<pii> A, B;
  while (K--) {
    int ni, mi, ci; cin >> ni >> mi >> ci; --ni; --mi;
    if (ci) A.emplace_back(ni, mi);
    else B.emplace_back(ni, mi);
  }

  N = A.size(), M = B.size();
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    auto [a1, b1] = A[i]; auto [a2, b2] = B[j];
    if (a1 != a2 && b1 != b2) continue;
    adj[i].push_back(j);
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; ++i) {
    if (ma[i] != -1) continue;
    memset(vis, false, sizeof vis);
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
