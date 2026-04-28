#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

// Assume a >= b
int r(int a, int b) {
  if (b == 0) return INF;
  if (b == 1) return a - 1;

  return a / b + r(b, a % b);
}

void solve() {
  int N; cin >> N;

  int ans = INF;
  for (int i = 1; i <= (N + 1) / 2; i++) {
    ans = min(ans, r(N, i));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
