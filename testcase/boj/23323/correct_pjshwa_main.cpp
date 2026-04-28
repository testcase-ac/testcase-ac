#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n, m;
  cin >> n >> m;

  ll day = 0;
  while (n) {
    n >>= 1;
    day++;
  }

  cout << day + m << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
