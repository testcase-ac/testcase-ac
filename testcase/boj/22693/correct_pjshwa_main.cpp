#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve(int n, string m) {
  int sz = m.size();

  __int128_t sum = 0, pow = 1;
  for (int i = sz - 1; i >= 0; i--) {
    sum += (m[i] >= 'A' ? m[i] - 'A' + 10 : m[i] - '0') * pow;
    pow *= n;
  }

  map<int, int> t;
  int dn = n;
  for (int i = 2; i <= n; i++) {
    while (dn % i == 0) {
      dn /= i;
      t[i]++;
    }
  }

  ll ans = 9e18;
  for (auto [k, v] : t) {
    __int128_t p = k;

    ll cur = 0;
    while (p <= sum) {
      cur += (sum / p);
      p *= k;
    }

    ans = min(ans, cur / v);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    int n;
    string m;
    cin >> n >> m;
    if (n == 0 && m == "0") break;

    solve(n, m);
  }
}
