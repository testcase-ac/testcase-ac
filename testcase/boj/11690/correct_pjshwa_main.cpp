#include <iostream>
#include <vector>
#include <cstring>
#define ll long long
#define MOD ((ll)1 << 32)
using namespace std;

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

const ll MAX = 1e8;
bool p[MAX + 1];

int main() {
  fast_io();

  ll n, ans, c;
  vector<int> pr;

  memset(p, true, sizeof(p));
  for (ll i = 2; i <= MAX; ++i) {
    if (!p[i]) continue;
    pr.push_back(i);
    for (ll j = i * i; j <= MAX; j += i) p[j] = false;
  }

  cin >> n;
  ans = 1;

  for (int &prime : pr) {
    if (prime > n) break;

    c = 1;
    while (c * prime <= n) c *= prime;

    ans *= c;
    ans %= MOD;
  }

  cout << ans << '\n';
}
