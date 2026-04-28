#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int LIM = 75;
const ll MAX = 1e9 / LIM;
ll lp[MAX + 1];

ll f(ll mid, ll p) {
  vector<int> primes;
  for (int i = 2; i < p; i++) if (lp[i] == i) primes.push_back(i);

  ll ret = mid, sz = primes.size();
  for (int state = 1; state < (1 << sz); state++) {
    ll d = 1, sgn = -1;

    for (int i = 0; i < sz; i++) {
      if (state & (1 << i)) {
        d *= primes[i];
        if (d > mid) break;
        sgn *= -1;
      }
    }
    ret -= sgn * mid / d;
  }

  return ret;
}

int main() {
  fast_io();

  ll n, p;
  cin >> n >> p;

  vector<int> pr;

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  if (p > LIM) {
    if (n == 1) cout << p;
    else {
      n--;
      for (int i = p; i <= MAX; i++) {
        if (p * i > 1e9) break;
        if (lp[i] >= p) n--;
        if (!n) {
          cout << p * i;
          break;
        }
      }
      if (n) cout << 0;
    }
  }
  else {

    ll left = 1;
    ll right = 1e9 / p;
    ll mid = (left + right) / 2;

    while (left < right) {
      if (f(mid, p) < n) left = mid + 1;
      else right = mid;

      mid = (left + right) / 2;
    }

    cout << (f(mid, p) == n ? mid * p : 0);
  }

}
