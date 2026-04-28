#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
ll d[MAX + 1];

ll T(ll n, ll r) {
  if (d[n] != -1) return d[n];
  if (n == 1) return d[1] = 1;

  ll k = n - round(sqrt(2 * n + 1)) + 1, res;
  if (n - k > 63) res = 0;
  else res = 2 * T(k, r) + (1LL << (n - k)) - 1;
  return d[n] = res;
}

int tc, n;
void solve() {
  cout << "Case " << ++tc << ": " << T(n, 4) << '\n';
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));
  while (cin >> n) solve();
}
