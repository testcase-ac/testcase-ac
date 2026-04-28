#include <bits/stdc++.h>
#define ll long long
using namespace std;

int N;
ll a[1'000'000];

ll phi(ll n) {
  ll result = n;
  for (ll i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      while (n % i == 0) n /= i;
      result -= result / i;
    }
  }
  if (n > 1) result -= result / n;
  return result;
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

ll f(ll c, ll mod) {
  if (mod == 1) return 0;
  if (c == N - 2 && a[c + 1] <= 30) return lpow(a[c], a[c + 1], mod);
  if (c == N - 1) return a[c] % mod;
  return lpow(a[c], f(c + 1, phi(mod)) + phi(mod), mod);
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int t, m;
  cin >> t >> m;

  while (t--) {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < N; i++) {
      if (a[i] == 1) {
        N = i;
        break;
      }
    }

    while (N > 1) {
      if (a[N - 2] <= 100 && a[N - 1] <= 5) {
        a[N - 2] = lpow(a[N - 2], a[N - 1], 1e18);
        N--;
      }
      else break;
    }

    cout << (N == 0 ? 1 : f(0, m)) << '\n';
  }
}
