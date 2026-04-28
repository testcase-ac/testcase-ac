#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll C(int n, int k) {
  ll ans = 1;
  for (int i = 1; i <= k; i++) {
    ans *= (n - i + 1);
    ans /= i;
  }
  return ans;
}

ll a[101];
const int MOD = 1e9 + 7;
int main() {
  fast_io();

  a[0] = 1;
  for (int i = 1; i <= 100; i++) a[i] = (i * a[i - 1] + (i & 1 ? MOD - 1 : 1)) % MOD;

  int n;
  cin >> n;
  cout << a[(n / 4) * 4] * C(n, n % 4) % MOD;
}
