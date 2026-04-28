#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, x;
  cin >> n;

  ll ans = 0;
  map<int, int> cnt;
  for (int i = 0; i < n; i++) {
    cin >> x;
    for (int j = x; j <= n; j += x) ans += cnt[j];
    cnt[x]++;
  }
  cout << ans << '\n';
}
