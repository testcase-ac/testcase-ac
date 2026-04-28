#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll pf[10001];
int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  pf[0] = 0;
  int s;
  for (int i = 0; i < n; i++) {
    cin >> s;
    pf[i + 1] = pf[i] + s;
  }

  int lp = 0, rp = 1;
  int ans = 0;

  ll ps;
  while (rp <= n) {
    ps = pf[rp] - pf[lp];
    if (ps <= m) {
      if (ps == m) ans++;
      rp++;
    }
    else lp++;
  }

  cout << ans << '\n';
}
