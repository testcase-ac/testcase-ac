#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5, MOD = 998244353;
int A[MAX], B[MAX], B_inv[MAX + 1];

ll dfs(int as, int ae, int bs, int be) {
  if (as == ae) return A[as] == B[bs];

  int root = A[as + 1];
  int b_idx = B_inv[root];
  if (b_idx < bs || b_idx > be) return 0;

  ll left_sz = b_idx - bs + 1, ret;
  if (left_sz == ae - as) {
    ret = dfs(as + 1, ae, bs, b_idx) * 2 % MOD;
  }
  else {
    ret = dfs(as + 1, as + left_sz, bs, b_idx);
    ret = ret * dfs(as + left_sz + 1, ae, b_idx + 1, be - 1) % MOD;
  }
  return ret;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < N; i++) {
    cin >> B[i];
    B_inv[B[i]] = i;
  }
  if (A[0] != B[N - 1]) return cout << "0\n", void();
  cout << dfs(0, N - 1, 0, N - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
