#include <iostream>
#include <vector>
#define ll long long
#define MOD int(1e9 + 7)
using namespace std;

void swap(ll& a, ll& b) {
  ll temp = a;
  a = b;
  b = temp;
}

ll lpow(ll x, ll y, ll m){
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const ll MAX = 15000000;
ll lp[MAX + 1];

int main() {
  fast_io();

  ll n, m, c, exp, ans, tpow;
  vector<int> pr;

  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  cin >> n >> m;
  if (n < m) swap(n, m);

  ans = 1;
  for (int &prime : pr) {
    if (prime > m) break;

    exp = 1;
    tpow = 0;
    c = prime;
    while (c <= m) {
      tpow += (n / c) * (m / c);
      exp++;
      c *= prime;
    }

    ans *= lpow(prime, tpow, MOD);
    ans %= MOD;
  }

  cout << ans << '\n';
}
