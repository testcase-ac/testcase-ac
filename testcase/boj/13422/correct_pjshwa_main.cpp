#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int geld[100000];
int main() {
  fast_io();

  int t, m, n, k, ans;
  cin >> t;

  ll sum;
  while (t--) {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) cin >> geld[i];

    sum = 0;
    for (int i = 0; i < m; i++) sum += geld[i];

    if (n == m) {
      cout << (sum < k) << '\n';
      continue;
    }

    ans = 0;
    for (int i = 0; i < n; i++) {
      if (sum < k) ans++;
      sum = sum + geld[(i + m) % n] - geld[i];
    }

    cout << ans << '\n';
  }
}
