#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e6;
int m[MAX + 1];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    m[x]++;
  }

  ll ans = 0;
  for (ll v = 1; v <= MAX; v++) {
    int cnt = 0;
    for (int j = v; j <= MAX; j += v) {
      cnt += m[j];
    }
    if (cnt > 1) ans = max(ans, v * cnt);
  }
  cout << ans << '\n';
}
