#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e4;
int P[MAXN + 10], Next[MAXN + 10], dp[MAXN + 10];
pii A[MAXN + 10];
vector<int> G[MAXN + 10];
int N;

int dfs(int u) {
  if (dp[u] != -1) return dp[u];

  auto [p, t] = A[u];
  if (Next[u] == N) return dp[u] = N - p - t;

  int ret = 0, add = Next[u] - p - t;
  for (int i : G[Next[u]]) ret = max(ret, dfs(i) + add);
  return dp[u] = ret;
}

void solve() {
  int K; cin >> N >> K;
  P[N] = 1;

  for (int i = 1; i <= K; ++i) {
    int p, t; cin >> p >> t; --p;
    A[i] = {p, t}; P[p] = 1;
  }
  sort(A + 1, A + K + 1);

  Next[0] = A[1].first;
  for (int i = 1; i <= K; ++i) {
    auto [p, t] = A[i];
    Next[i] = p + t;
    while (!P[Next[i]]) ++Next[i];
    G[p].push_back(i);
  }

  memset(dp, -1, sizeof(dp));
  cout << dfs(0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
