#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int a[MAX];
ll d[MAX][MAX + 1];
int n, k;

void solve() {
  memset(d, 0, sizeof(d));

  for (int i = 0; i < n; i++) cin >> a[i];
  d[0][1] = 1;
  for (int i = 1; i < n; i++) {
    d[i][1] = 1;
    for (int l = 2; l <= k; l++) for (int j = 0; j < i; j++) {
      if (a[j] < a[i]) d[i][l] += d[j][l - 1];
    }
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) ans += d[i][k];
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n >> k;
    if (n == 0 && k == 0) break;
    solve();
  }
}
