#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[5][4];

void solve() {
  for (int i = 1; i <= 4; i++) for (int j = 0; j < 4; j++) cin >> a[i][j];

  int outer[4] = {
    max(a[2][2], a[3][2]),
    max(a[3][3], a[4][3]),
    min(a[1][2], a[4][2]),
    min(a[1][3], a[2][3])    
  };
  int inner[4] = {
    min(a[2][0], a[3][0]),
    min(a[3][1], a[4][1]),
    max(a[1][0], a[4][0]),
    max(a[1][1], a[2][1])
  };

  if (inner[0] < outer[0]) return cout << "0\n", void();
  if (inner[1] < outer[1]) return cout << "0\n", void();
  if (inner[2] > outer[2]) return cout << "0\n", void();
  if (inner[3] > outer[3]) return cout << "0\n", void();

  ll ans = 0, v1 = 0, v2 = 0, dt1 = 0, dt2 = 0;
  for (int k = -2 * MAX; k <= 2 * MAX; k++) {
    if (inner[3] == outer[2] + k) v1++;
    if (outer[1] == inner[0] + k) v2++;

    v1 += dt1;
    v2 += dt2;
    ans += v1 * v2;

    if (outer[3] == inner[2] + k) v1--;
    if (inner[1] == outer[0] + k) v2--;

    if (inner[3] == outer[2] + k) dt1++;
    if (outer[3] == inner[2] + k) dt1++;

    if (outer[3] == outer[2] + k) dt1--;
    if (inner[3] == inner[2] + k) dt1--;

    if (outer[1] == inner[0] + k) dt2++;
    if (inner[1] == outer[0] + k) dt2++;

    if (inner[1] == inner[0] + k) dt2--;
    if (outer[1] == outer[0] + k) dt2--;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
