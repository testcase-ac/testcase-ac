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

bool ef(ll n) {
  set<int> u;
  for (int i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      n /= i;
      u.insert(i);
    }
  }
  if (n > 1) u.insert(n);
  return u.size() % 2 == 0;
}

void solve() {
  int N;
  cin >> N;
  if (N == 1) return cout << "3\n", void();

  bool E = false, L = false;
  if (N > 5 && (N / 1000 + N / 100 + N / 10 + N % 10) % 2 == 1) E = true;
  if (N == 2 || N == 4) L = true;
  if (!is_prime(N) && ef(N)) L = true;

  if (E) {
    if (L) cout << "4\n";
    else cout << "1\n";
  }
  else {
    if (L) cout << "2\n";
    else cout << "3\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
