#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 18, MAXV = 100;
int A[MAXN], dp[1 << MAXN][MAXV + 1], Z;

int rec(int s, int v) {
  if (s == 0) return 1;
  if (dp[s][v] != -1) return dp[s][v];

  int ret = 0;
  for (int i = 0; i < Z; ++i) {
    if (!(s & (1 << i))) continue;
    if (A[i] % v != 0 || A[i] / v > MAXV) continue;
    ret |= rec(s ^ (1 << i), A[i] / v);
  }
  return dp[s][v] = ret;
}

void trace(int s, int v) {
  if (s == 0) cout << v << '\n';
  else {
    for (int i = 0; i < Z; ++i) {
      if (!(s & (1 << i))) continue;
      if (A[i] % v != 0 || A[i] / v > MAXV) continue;
      if (rec(s ^ (1 << i), A[i] / v)) {
        cout << v << ' ';
        trace(s ^ (1 << i), A[i] / v);
        return;
      }
    }
  }
}

void solve() {
  int N; cin >> N; Z = N - 1;
  for (int i = 0; i < Z; ++i) cin >> A[i];

  memset(dp, -1, sizeof dp);
  for (int v = 1; v <= MAXV; ++v) {
    if (rec((1 << Z) - 1, v)) {
      cout << "Yes\n";
      return trace((1 << Z) - 1, v);
    }
  }
  cout << "No\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
