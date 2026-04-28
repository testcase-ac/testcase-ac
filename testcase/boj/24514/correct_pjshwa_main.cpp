#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
ll a[MAX];
int l, k;

int r(int n) {
  if (n == 1) return 1;

  auto it = lower_bound(a, a + l, n);
  it--;
  int offset = n - *it - 1;
  int i = it - a;

  ll la = a[i], lb = a[i - 1];
  if (offset < la - lb) return r(n - la + lb);
  else {
    offset -= la - lb;
    vector<int> res;
    int oi = i + 1;
    while (oi) {
      res.push_back(oi % k);
      oi /= k;
    }
    reverse(res.begin(), res.end());
    return res[offset];
  }
}

void solve() {
  int q;
  cin >> q >> k;

  a[1] = 1;
  for (int i = 2;; i++) {
    a[i] = 2 * a[i - 1] - a[i - 2];
    ll oi = i, oc = 0;
    while (oi) {
      oi /= k;
      oc++;
    }
    a[i] += oc;
    if (a[i] >= 2e9) {
      l = i;
      break;
    }
  }

  while (q--) {
    int n;
    cin >> n;
    cout << r(n) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
