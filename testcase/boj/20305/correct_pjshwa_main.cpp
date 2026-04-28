#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, MOD = 1e9 + 7;
int in[MAX + 1], f[MAX + 1];
vector<int> out[MAX + 1];

void solve() {
  int n, q;
  cin >> n >> q;
  while (q--) {
    int a, b;
    cin >> a >> b;
    in[a]++;
    out[b].push_back(b - a + 1);
  }

  int d1 = 0, d2 = 0, d3 = 0;
  for (int i = 1; i <= n; i++) {
    int tmp = (d1 + d2) % MOD;
    d3 = (tmp + in[i]) % MOD;

    cout << d3 << ' ';

    d1 = d2, d2 = d3;
    for (int p : out[i]) {
      d2 = (d2 + MOD - f[p]) % MOD;
      d1 = (d1 + MOD - f[p - 1]) % MOD;
    }
  }

  cout << '\n';

}

int main() {
  fast_io();

  f[0] = 0, f[1] = 1, f[2] = 1;
  for (int i = 3; i <= MAX; i++) f[i] = (f[i - 1] + f[i - 2]) % MOD;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
