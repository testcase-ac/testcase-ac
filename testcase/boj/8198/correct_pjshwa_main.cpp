#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
ll p[MAX], nxt[62][MAX];

void solve() {
  ll n, k, m;
  cin >> n >> k >> m;
  for (int i = 0; i < n; i++) cin >> p[i];

  int s = 0, e = k;
  nxt[0][0] = e;
  for (int i = 1; i < n; i++) {
    while (e < n - 1 && p[i] - p[s] > p[e + 1] - p[i]) s++, e++;

    if (p[i] - p[s] >= p[e] - p[i]) nxt[0][i] = s;
    else nxt[0][i] = e;
  }

  for (int j = 0; j < 62; j++) for (int i = 0; i < n; i++) nxt[j + 1][i] = nxt[j][nxt[j][i]];

  for (int i = 0; i < n; i++) {
    ll d = m, v = i;
    for (int j = 61; j >= 0; j--) {
      if ((1LL << j) > d) continue;
      v = nxt[j][v];
      d -= 1LL << j;
    }

    cout << v + 1 << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
