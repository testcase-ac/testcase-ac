#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int a[3];
  for (int i = 0; i < 3; i++) cin >> a[i];
  sort(a, a + 3);

  if (a[0] + a[1] == a[2]) cout << "1\n";
  else if (a[0] * a[1] == a[2]) cout << "2\n";
  else cout << "3\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
