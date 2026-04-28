#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool in_range(int x1, int y1, int x2, int y2) {
  if (x1 == x2 || y1 == y2) return true;
  if (abs(x1 - x2) == abs(y1 - y2)) return true;
  return false;
}

const int MAXK = 1e5;
int X[MAXK], Y[MAXK];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < K; ++i) cin >> X[i] >> Y[i];

  int ans = 0;
  for (int x = 1; x <= N; ++x) for (int y = 1; y <= N; ++y) {
    if (!in_range(x, y, X[0], Y[0])) continue;

    bool ok = true;
    for (int i = 0; i < K; ++i) ok &= in_range(x, y, X[i], Y[i]);
    ans += ok;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
