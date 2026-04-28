#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 300;
ld d[MAX + 1];
int n;

// probability that your seat is taken by another passenger
// if i-th passenger's seat is taken by someone else
ld f(int i) {
  if (i == n) return 1.0;
  if (d[i] != -1) return d[i];

  // you can either take seat #1 or seats #i+1 ~ #n, each with probability 1 / (n - i + 1)
  // if you take seat #1, the probability in question is 0
  ld ret = 0;
  for (int j = i + 1; j <= n; ++j) ret += f(j) / (n - i + 1);
  return d[i] = ret;
}

void solve() {
  cin >> n;

  fill(d, d + n, -1);
  ld ans = 0;
  for (int i = 2; i <= n; ++i) ans += f(i) / (n - 1);
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
