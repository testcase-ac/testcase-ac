#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll n, k;
  cin >> n >> k;
  n--;

  int cn = sqrt(2.0 * n / k), fn;
  if (cn * (cn - 1) / 2 * k > n) fn = cn - 1;
  else if (cn * (cn + 1) / 2 * k > n) fn = cn;
  else fn = cn + 1;

  bool dir = fn & 1;
  int spos = fn / 2;
  spos *= (dir ? -k : k);

  n -= fn * (fn - 1) / 2 * k;
  cout << spos + (dir ? n : -n) << ' ' << (dir ? 'R' : 'L') << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
