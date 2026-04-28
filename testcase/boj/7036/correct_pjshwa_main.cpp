#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 1000, INF = 1e18;
ll dp[MAXN + 1][MAXN + 1][2], N, P;
vector<int> L, R;

ll rec(int li, int ri, int p) {
  if (dp[li][ri][p] != -1) return dp[li][ri][p];

  ll ret, cpos, mul = N - (li + ri);
  if (p == 0) {
    if (li == 0) cpos = P;
    else cpos = L[li - 1];
  }
  else {
    if (ri == 0) cpos = P;
    else cpos = R[ri - 1];
  }

  if (li == L.size()) {
    if (ri == R.size()) ret = 0;
    else ret = rec(li, ri + 1, 1) + abs(cpos - R[ri]) * mul;
  }
  else if (ri == R.size()) {
    ret = rec(li + 1, ri, 0) + abs(cpos - L[li]) * mul;
  }
  else {
    ret = min(rec(li + 1, ri, 0) + abs(cpos - L[li]) * mul,
              rec(li, ri + 1, 1) + abs(cpos - R[ri]) * mul);
  }
  return dp[li][ri][p] = ret;
}

void solve() {
  cin >> N >> P;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    if (x <= P) L.push_back(x);
    else R.push_back(x);
  }
  sort(L.begin(), L.end(), greater<int>());
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
