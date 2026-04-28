#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n;
  cin >> n;

  int p[n];
  iota(p, p + n, 0);

  int ans = n;
  do {
    int dd[n]{}, da[n]{};
    for (int i = 0; i < n; i++) {
      dd[i] = da[i] = 1;
      for (int j = i - 1; j >= 0; j--) {
        if (p[j] < p[i]) da[i] = max(da[i], da[j] + 1);
        if (p[j] > p[i]) dd[i] = max(dd[i], dd[j] + 1);
      }
    }

    ans = min(ans, max(*max_element(dd, dd + n), *max_element(da, da + n)));

  } while (next_permutation(p, p + n));

  cout << ans << endl;

  do {
    int dd[n]{}, da[n]{};
    for (int i = 0; i < n; i++) {
      dd[i] = da[i] = 1;
      for (int j = i - 1; j >= 0; j--) {
        if (p[j] < p[i]) da[i] = max(da[i], da[j] + 1);
        if (p[j] > p[i]) dd[i] = max(dd[i], dd[j] + 1);
      }
    }

    int cur = max(*max_element(dd, dd + n), *max_element(da, da + n));
    if (cur == ans) {
      for (int i = 0; i < n; i++) cout << p[i] + 1 << ' ';
      cout << endl;
      return;
    }

  } while (next_permutation(p, p + n));


}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
