#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int mod = 1e9 + 7;
int a[(int)3e5];
ll pows[(int)3e5];
int main() {
  fast_io();

  int n;
  cin >> n;

  pows[0] = 1;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (i) pows[i] = (pows[i - 1] * 2) % mod;
  }
  sort(a, a + n);

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans = (ans + a[i] * (pows[i] - pows[n - i - 1])) % mod;
  }
  cout << (ans + mod) % mod << '\n';
}
