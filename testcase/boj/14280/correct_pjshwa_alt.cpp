#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int BIAS = 5e5;

ll a, b, c;
ll f(ll A, ll B) {
  return abs(A - a) + abs(B - b) + abs(A * B - c);
}

void solve() {
  cin >> a >> b >> c;

  ll ans = f(a, b);
  for (int i = 1; i * i <= c; i++) {
    ans = min(ans, f(i, c / i));
    ans = min(ans, f(i, c / i + 1));
    ans = min(ans, f(c / i, i));
    ans = min(ans, f(c / i + 1, i));
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
