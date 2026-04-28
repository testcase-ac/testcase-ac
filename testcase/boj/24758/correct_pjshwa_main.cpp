#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll a, b, oa, ob;
  cin >> a >> b;
  oa = a, ob = b;

  bool aprime = true, bprime = true;

  map<ll, int> f;
  for (ll i = 2; i * i <= oa; i++) {
    if (a % i) continue;

    aprime = false;
    while (a % i == 0) {
      f[i]++;
      a /= i;
    }
  }
  if (a > 1) f[a]++;

  for (ll i = 2; i * i <= ob; i++) {
    if (b % i) continue;

    bprime = false;
    while (b % i == 0) {
      f[i]++;
      b /= i;
    }
  }
  if (b > 1) f[b]++;

  if (aprime && bprime && a != b) cout << "full credit\n";
  else {
    for (auto& [k, v] : f) {
      if (v > 1) return cout << "no credit\n", void();
    }
    cout << "partial credit\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
