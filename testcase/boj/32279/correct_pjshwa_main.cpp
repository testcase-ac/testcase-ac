#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 20, MOD = 1e9 + 7;
ll A[MAXN + 1];

void solve() {
  ll N, p, q, r, s; cin >> N >> p >> q >> r >> s >> A[1];

  ll S = A[1];
  for (int i = 2; i <= N; ++i) {
    if (i & 1) A[i] = r * A[i / 2] + s;
    else A[i] = p * A[i / 2] + q;
    S += A[i];
  }
  cout << S << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
