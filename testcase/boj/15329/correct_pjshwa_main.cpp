#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
ll d[2][MAX + 1];

int main() {
  fast_io();

  int l, k;
  cin >> l >> k;
  
  d[1][0] = 1;
  for (int i = 1; i <= l; i++) {
    d[0][i] += d[1][i - 1];
    d[1][i] += d[0][i - 1];
    if (i >= k) d[0][i] += d[1][i - k];
  }

  ll ans = 0;
  for (int i = 1; i <= l; i++) ans += d[0][i];
  cout << ans << '\n';
}
