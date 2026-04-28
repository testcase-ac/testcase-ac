#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;
  vector<string> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  bool f = false;
  for (int i = 1; i < n; i++) {
    if (a[i].size() != a[i - 1].size()) continue;

    string s = a[i - 1], t = a[i];
    s[0] = '9', t[0] = t.size() == 1 ? '0' : '1';

    if (stoll(s) > stoll(a[i])) a[i - 1] = s;
    else if (stoll(t) < stoll(a[i - 1])) a[i] = t;
    else continue;

    f = true;
    break;
  }

  if (f) {
    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << '\n';
  }
  else cout << "impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
