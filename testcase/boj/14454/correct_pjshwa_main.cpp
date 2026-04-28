#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  ll k;
  cin >> s >> k;

  ll n = s.size();
  while (n < k) n <<= 1;

  while (n != s.size()) {
    ll d = n / 2;
    if (k > d) {
      if (k == d + 1) k = d;
      else k = k - 1 - d;
    }
    n = d;
  }
  cout << s[k - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
