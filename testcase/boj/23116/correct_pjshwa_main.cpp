#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

void solve() {
  int n;
  cin >> n;

  int s = (1 << 20) - 1;
  for (int i = 0; i < n; i++) cin >> a[i], s &= a[i];

  bool able = false;
  for (int i = 0; i < n; i++) able |= s == a[i];

  if (able) {
    cout << 2 * n << '\n';
    for (int i = 0; i < n; i++) cout << a[i] << ' ' << s << ' ';
    cout << '\n';
  }
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
