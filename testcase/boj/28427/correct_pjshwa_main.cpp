#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
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

const int MAX = 5e5;
int D[MAX + 1];

void solve() {
  for (int i = 1; i <= MAX; i++) {
    if (is_prime(2 * i + 1)) D[i] = 1;
    D[i] += D[i - 1];
  }

  int Q; cin >> Q;
  while (Q--) {
    int l, r; cin >> l >> r;
    cout << D[r - 1] - D[l - 1] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
