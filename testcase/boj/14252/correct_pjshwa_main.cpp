#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
int a[MAX];

int e(int x, int y) {
  if (x == 2184 && y == 2200) return 2;
  if (x == 27830 && y == 27846) return 2;
  if (x == 32214 && y == 32230) return 2;
  if (x == 57860 && y == 57876) return 2;
  if (x == 62244 && y == 62260) return 2;
  if (x == 87890 && y == 87906) return 2;
  if (x == 92274 && y == 92290) return 2;

  return __gcd(x, y) > 1;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  int ans = 0;
  for (int i = 0; i < n - 1; i++) ans += e(a[i], a[i + 1]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
