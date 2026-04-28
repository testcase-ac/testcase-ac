#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, MOD = 1e9 + 7;
int A[MAXN][MAXN];

void solve() {
  int N, M, D; cin >> N >> M >> D;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) cin >> A[i][j], A[i][j] += D * i;
    sort(A[i], A[i] + M);
  }

  ll ans = 1;
  for (int j = 1; j <= M; ++j) ans = ans * j % MOD;

  for (int i = 1; i < N; ++i) {
    int pj = 0; ll cur = 1;
    for (int j = 0; j < M; ++j) {
      while (pj < M && A[i - 1][pj] < A[i][j]) ++pj;
      cur = cur * max(0, pj - j) % MOD;
    }
    ans = ans * cur % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
