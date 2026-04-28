#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

const int MAX = 1e6;

ll ask() {
  ll x;
  cin >> x;
  return x;
}

void say(ll x, ll y) {
  cout << x << ' ' << y << endl;
}

void solve() {
  ll d;

  say(0, 0);
  d = ask();
  if (d == 0) return;

  vector<pll> candidates;
  for (ll i = 0; i * i <= d; i++) {
    ll j2 = d - i * i, j = sqrt(j2);
    if (j * j == j2) candidates.push_back({i, j});
  }

  for (auto& [a, b] : candidates) {
    if (a > MAX || b > MAX || a < 0 || b < 0) continue;

    say(a, b);
    if (ask() == 0) return;
  }
}

int main() {
  int t = 1;
  cin >> t;
  while (t--) solve();
}
