#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n, k1, a; cin >> n >> k1 >> a;

  unordered_set<ll> U{k1};
  ll nk = (k1 + a * k1 * k1) % n;
  while (!U.count(nk)) {
    U.insert(nk);
    nk = (k1 + a * nk * nk) % n;
  }
  cout << U.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
