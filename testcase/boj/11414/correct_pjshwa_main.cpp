#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll lcm(ll x, ll y) { return x / __gcd(x, y) * y; }

int main() {
  fast_io();

  int a, b;
  cin >> a >> b;
  if (a == b) {
    cout << "1\n";
    return 0;
  }

  int k = abs(b - a);
  vector<int> k_factors;

  for (int i = 1; i <= sqrt(k); i++) {
    if (k % i == 0) {
      k_factors.push_back(i);
      if (i != k / i) k_factors.push_back(k / i);
    }
  }

  long long mv = 2e18, mn, cv, cn;
  for (int factor : k_factors) {
    cn = (a / factor + 1) * factor - a;
    cv = lcm(a + cn, b + cn);
    if (cv < mv) {
      mv = cv;
      mn = cn;
    }
  }
  cout << mn << '\n';
}
