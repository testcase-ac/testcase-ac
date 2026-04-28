#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, BIAS = 50;
vector<int> adj[MAXN];
int par[MAXN], vis[MAXN];

bool dfs(int a) {
  for (int b : adj[a]) {
    if (vis[b]) continue;
    vis[b] = 1;
    if (par[b] == -1 || dfs(par[b])) {
      par[b] = a;
      return true;
    }
  }
  return false;
}

void solve() {
  int N; cin >> N;
  vector<int> A(N), B(N), C(N);
  for (int i = 0; i < N; ++i) cin >> A[i] >> B[i] >> C[i];
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (A[i] < A[j] || B[i] < B[j] || C[i] < C[j]) continue;
    if (A[i] == A[j] && B[i] == B[j] && C[i] == C[j] && i <= j) continue;
    adj[i].push_back(j + BIAS);
  }

  memset(par, -1, sizeof par);
  for (int i = 0; i < N; i++) {
    memset(vis, 0, sizeof vis); dfs(i);
    memset(vis, 0, sizeof vis); dfs(i);
  }

  int match = 0;
  for (int i = 0; i < N; ++i) match += par[i + BIAS] == -1;
  cout << match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
