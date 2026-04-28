#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
vector<int> adj[MAXN];
int ma[MAXN], mb[MAXN], A[MAXN], B[MAXN], N, M;
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
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < M; ++i) cin >> B[i];

  for (int i = 0; i < N; ++i) adj[i].clear();
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (gcd(A[i], B[j]) > 1) adj[i].push_back(j);
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; i++) {
    if (ma[i] != -1) continue;
    memset(vis, 0, sizeof vis);
    if (dfs(i)) ++match;
  }
  cout << match << '\n';
}

int main() {
  fast_io();

  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
