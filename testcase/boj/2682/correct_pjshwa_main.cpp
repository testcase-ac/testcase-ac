#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll fac[21];
ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;

  ll a = 1;
  for (int i = 0; i < k; i++) {
    a *= (n - i);
    a /= (i + 1);
  }
  return a;
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int t;
  cin >> t;

  fac[0] = 1;
  for (int i = 1; i <= 20; i++) fac[i] = fac[i - 1] * i;

  while (t--) {
    int n, k;
    cin >> n >> k;

    if (k == 1) {
      cout << fac[n - 1] << '\n';
      continue;
    }

    ll a = 0;
    for (int i = 0; i <= k - 2; i++) a += C(k - 2, i) * fac[n - 2 - i] * fac[1 + i];

    cout << a << '\n';
  }
}
