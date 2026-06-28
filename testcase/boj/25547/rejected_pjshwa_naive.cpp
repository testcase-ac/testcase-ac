#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll lcm(ll a, ll b) {
  return a / __gcd(a, b) * b;
}

void solve() {
  int A, B;
  cin >> A >> B;
  for (int C = 1; C <= 1e5; C++) {
    if (__gcd(A, B) == __gcd(A, C) && lcm(A, B) == lcm(B, C)) {
      cout << C << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
