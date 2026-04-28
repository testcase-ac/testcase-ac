#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll s[41];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  s[0] = s[1] = 1, s[2] = 2;
  for (int i = 3; i <= 40; i++) s[i] = s[i - 1] + s[i - 2];

  int x, last = 0;
  int ans = 1;
  for (int i = 0; i < m; i++) {
    cin >> x;
    ans *= s[x - last - 1];
    last = x;
  }
  ans *= s[n - last];
  cout << ans << '\n';
}
