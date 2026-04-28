#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll a[3][3];
int tc;

bool is_aprog(ll a, ll b, ll c) {
  return 2 * b == a + c;
}

int check() {
  int cur = 0;
  for (int i = 0; i < 3; i++) {
    if (is_aprog(a[i][0], a[i][1], a[i][2])) cur++;
  }
  for (int j = 0; j < 3; j++) {
    if (is_aprog(a[0][j], a[1][j], a[2][j])) cur++;
  }
  if (is_aprog(a[0][0], a[1][1], a[2][2])) cur++;
  if (is_aprog(a[0][2], a[1][1], a[2][0])) cur++;
  return cur;
}

void solve() {
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
    if (i == 1 && j == 1) continue;
    cin >> a[i][j];
  }

  int ans = 0;

  a[1][1] = (a[0][1] + a[2][1]) / 2;
  ans = max(ans, check());

  a[1][1] = (a[1][0] + a[1][2]) / 2;
  ans = max(ans, check());

  a[1][1] = (a[0][0] + a[2][2]) / 2;
  ans = max(ans, check());

  a[1][1] = (a[0][2] + a[2][0]) / 2;
  ans = max(ans, check());

  cout << "Case #" << ++tc << ": " << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
