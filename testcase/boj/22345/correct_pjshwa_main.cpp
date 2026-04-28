#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
pll a[MAX];
ll b[MAX], pl[MAX], pr[MAX], psl[MAX], psr[MAX];

void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) cin >> a[i].second >> a[i].first, b[i] = a[i].first;
  sort(a, a + n);
  sort(b, b + n);

  psl[0] = a[0].second;
  for (int i = 1; i < n; i++) {
    pl[i] = pl[i - 1] + psl[i - 1] * (a[i].first - a[i - 1].first);
    psl[i] = psl[i - 1] + a[i].second;
  }

  psr[n - 1] = a[n - 1].second;
  for (int i = n - 2; i >= 0; i--) {
    pr[i] = pr[i + 1] + psr[i + 1] * (a[i + 1].first - a[i].first);
    psr[i] = psr[i + 1] + a[i].second;
  }

  while (q--) {
    int x;
    cin >> x;
    auto it = upper_bound(b, b + n, x);

    if (it == b) {
      ll addend = (b[0] - x) * psl[n - 1];
      cout << pr[0] + addend << '\n';
    }
    else {
      it--;
      int idx = it - b;

      ll addend = (x - b[idx]) * psl[idx];
      if (idx < n - 1) {
        addend += (b[idx + 1] - x) * psr[idx + 1];
        addend += pr[idx + 1];
      }
      cout << pl[idx] + addend << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
