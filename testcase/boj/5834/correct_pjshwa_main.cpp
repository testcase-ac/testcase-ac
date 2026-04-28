#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
vector<int> L, R;
ll dp[MAXN + 1][MAXN + 1][2], Lz, Rz;

ll rec(int l, int r, int d) {
  if (dp[l][r][d] != -1) return dp[l][r][d];
  if (l == Lz && r == Rz) return dp[l][r][d] = 0;

  ll ret = 1e18, rem = Lz - l + Rz - r;
  if (d) {
    if (l < Lz) ret = min(ret, rec(l + 1, r, 0) + rem * (R[r] + L[l + 1]));
    if (r < Rz) ret = min(ret, rec(l, r + 1, 1) + rem * (R[r + 1] - R[r]));
  } else {
    if (l < Lz) ret = min(ret, rec(l + 1, r, 0) + rem * (L[l + 1] - L[l]));
    if (r < Rz) ret = min(ret, rec(l, r + 1, 1) + rem * (R[r + 1] + L[l]));
  }
  return dp[l][r][d] = ret;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    if (x < 0) L.push_back(-x);
    else R.push_back(x);
  }
  Lz = L.size(), Rz = R.size();
  L.push_back(0), R.push_back(0);
  sort(L.begin(), L.end());
  sort(R.begin(), R.end());

  memset(dp, -1, sizeof(dp));
  cout << rec(0, 0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
