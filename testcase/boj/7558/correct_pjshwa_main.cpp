#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

int tc;
void solve() {
  cout << "Scenario #" << ++tc << ":\n";

  ll a, p;
  cin >> a >> p;
  if (a < 0) a = p - (-a) % p;

  int ans = lpow(a, p * (p - 1) / 2, p);
  if (ans == 1) cout << "1\n";
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) {
    solve();
    if (t) cout << "\n";
  }
}
