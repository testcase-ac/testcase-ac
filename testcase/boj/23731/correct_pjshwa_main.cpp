#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n, pw = 1;
  cin >> n;

  while (pw <= n) {
    ll cn = n / pw;
    pw *= 10;
    if (cn % 10 >= 5) {
      n = (n / pw) * pw;
      n += pw;
    }
  }
  cout << n << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
