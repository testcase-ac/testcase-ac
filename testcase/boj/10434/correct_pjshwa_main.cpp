#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool is_prime(ll n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (ll i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

void solve() {
  int TC, N;
  cin >> TC >> N;
  cout << TC << ' ' << N << ' ';
  if (!is_prime(N)) return cout << "NO\n", void();

  set<int> v;
  v.insert(N);

  while (1) {
    if (N == 1) return cout << "YES\n", void();

    int nval = 0;
    while (N) {
      int d = N % 10;
      nval += d * d;
      N /= 10;
    }
    N = nval;
    if (v.count(N)) return cout << "NO\n", void();
    v.insert(N);
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
