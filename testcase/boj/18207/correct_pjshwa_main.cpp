#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 2e5, LIM = 1e15;
ll A[MAXN + 10], P[MAXN + 10], lr[MAXN + 10];

void solve() {
  int n; cin >> n;
  for (int i = 1; i <= n; ++i) cin >> A[i], P[i] = P[i - 1] + A[i];

  int li = n + 1;
  for (int i = n; i >= 1; --i) {
    lr[i] = li;
    if (A[i] > 1) li = i;
  }

  int ans = 0;
  for (int l = 1; l <= n - 1; ++l) {
    // start index = i
    // jump over groups of 1

    __int128_t sum = A[l], mul = A[l];
    int r = l;
    while (mul <= LIM) {
      int nr = lr[r];

      // Whether a reversal has happened
      if (sum < mul && P[nr - 1] - P[l - 1] >= mul) ++ans;
      if (nr > n) break;

      r = nr;
      sum = P[r] - P[l - 1];
      mul = mul * A[r];

      // Whether result is equal at this index
      if (sum == mul) ++ans;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
