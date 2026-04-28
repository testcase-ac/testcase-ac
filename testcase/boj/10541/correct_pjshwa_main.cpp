#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int p[26][MAX + 1], n;

int f(ll num) {
  ll x = (num % 2 == 0) ? num / 2 : num;
  x %= n;
  ll y = (num % 2 == 1) ? (num + 1) / 2 : num + 1;
  y %= n;
  return (x * y) % n;
}

void solve() {
  ll h; string s;
  cin >> h >> s;
  n = s.size();
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < 26; j++) p[j][i] = p[j][i - 1];
    p[s[i - 1] - 'A'][i]++;
  }

  int q;
  cin >> q;
  while (q--) {
    ll ai; string ci;
    cin >> ai >> ci;
    int cx = ci[0] - 'A';

    ll cnt = p[cx][n] * (ai / n);
    int l = f(ai - 1), r = f(ai);

    if (l > r) cnt += p[cx][n] - p[cx][l] + p[cx][r];
    else cnt += p[cx][r] - p[cx][l];

    cout << cnt << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
