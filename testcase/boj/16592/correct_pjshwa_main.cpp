#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll f(ll N) {
  if (N == 0) return 0;

  ll h = N / 2, rt = N / 10;
  return h + (N & 1) + f(rt);
}

void solve() {
  ll A, B;
  cin >> A >> B;
  ll fa = f(A - 1), fb = f(B);
  cout << fb - fa << ' ' << B - fb - (A - 1 - fa) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
