#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int lp[MAX + 1];
vector<int> pr;

void solve() {
  int a, b;
  cin >> a >> b;

  int g = __gcd(a, b);
  a /= g;
  b /= g;

  for (int i : pr) {
    if (i * i > 1e9) break;
    while (a % (i * i) == 0) a /= (i * i);
    while (b % (i * i) == 0) b /= (i * i);
  }

  vector<int> as, bs;
  for (int i = 1; i * i <= a; i++) if (a % i == 0) as.push_back(i), as.push_back(a / i);
  for (int i = 1; i * i <= b; i++) if (b % i == 0) bs.push_back(i), bs.push_back(b / i);

  ll e = (ll)a * b;
  ll msum = 1e18, ma, mb;
  for (int ae : as) for (int be : bs) {
    ll ce = (ll)ae * be;
    ll m = ce + (e / ce);
    if (m < msum) {
      msum = m;
      ma = ce;
      mb = e / ce;
    }
  }

  cout << ma << ' ' << mb << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t;
  cin >> t;
  while (t--) solve();
}
