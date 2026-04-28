#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX][MAX];
int rsum[MAX], csum[MAX], rosum[MAX], cosum[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cin >> a[i][j];
    rsum[i] += a[i][j];
    csum[j] += a[i][j];
    if (j & 1) rosum[i] += a[i][j];
    if (i & 1) cosum[j] += a[i][j];
  }

  int ans = 0, cur = 0;
  for (int i = 0; i < n; i++) cur += max(rsum[i] - rosum[i], rosum[i]);
  ans = max(ans, cur);

  cur = 0;
  for (int i = 0; i < n; i++) cur += max(csum[i] - cosum[i], cosum[i]);
  ans = max(ans, cur);

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
