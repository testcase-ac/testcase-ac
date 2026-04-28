#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int a[MAXN];

void solve() {
  int n, k, x; cin >> n >> k >> x;
  k = n * (n - 1) / 2 - k;

  int val = 1, str = 1, acc = 0; a[0] = 1;
  for (int i = 1; i < n; ++i) {
    if (acc + str <= k) {
      acc += str;
      ++str;
    }
    else {
      val += x;
      str = 1;
    }
    a[i] = val;
  }

  if (acc < k) cout << "-1\n";
  else {
    for (int i = 0; i < n; ++i) cout << a[i] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
