#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int ask(int l, int r) {
  if (l == r) return 0;

  cout << "? " << l << " " << r << endl;
  int res; cin >> res;
  return res;
}

void solve() {
  int n; cin >> n;

  int inv = ask(1, n);
  vector<int> a(n + 1), v(n + 1);
  for (int r = n - 1; r >= 1; --r) {
    int ninv = ask(1, r);
    int diff = inv - ninv, x = n;
    while (diff || v[x]) {
      if (!v[x]) --diff;
      --x;
    }
    a[r + 1] = x; v[x] = 1;
    inv = ninv;
  }
  int l;
  for (l = 1; l <= n; ++l) if (!v[l]) break;
  a[1] = l;

  // cout << "a = ";
  // for (int i = 1; i <= n; ++i) cout << a[i] << " ";
  // cout << endl;

  // Calculate LIS of a
  vector<int> lis;
  for (int i = 1; i <= n; ++i) {
    auto it = lower_bound(lis.begin(), lis.end(), a[i]);
    if (it == lis.end()) lis.push_back(a[i]);
    else *it = a[i];
  }
  cout << "! " << lis.size() << endl;
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
