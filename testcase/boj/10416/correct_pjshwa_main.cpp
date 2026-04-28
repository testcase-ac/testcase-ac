#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll C(int n, int k) {
  if (n < 0 || k < 0 || n < k) return 0;

  ll ans = 1;
  for (int i = 1; i <= k; i++) {
    ans *= (n - i + 1);
    ans /= i;
  }
  return ans;
}

ll H(int n, int k) {
  return C(n + k - 1, k);
}

void solve(int n) {
  vector<int> a(n);
  int sum = 0;
  for (int i = 0; i < n; i++) cin >> a[i], sum += a[i];

  ll ans = C(n + sum - 1, sum - 1);
  int rem = sum;
  for (int i = 0; i < n; i++) {
    rem -= a[i];
    for (int j = 0; j < a[i]; j++) ans += H(n - i - 1, rem + a[i] - j);
  }

  cout << ans + 1 << '\n';
}

int main() {
  fast_io();

  while (1) {
    int n;
    cin >> n;
    if (n == 0) break;

    solve(n);
  }
}
