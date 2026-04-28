#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

double d[51][1001];
int a[51];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 1; i <= k; i++) cin >> a[i];

  d[0][n] = 1;
  for (int i = 1; i <= k; i++) for (int pre = 0; pre <= n; pre++) {

  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
