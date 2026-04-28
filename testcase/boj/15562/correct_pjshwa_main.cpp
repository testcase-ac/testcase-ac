#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int out[MAX + 1], in[MAX + 1];

void solve() {
  int n, m;
  cin >> n >> m;
  while (m--) {
    int a, b;
    cin >> a >> b;
    out[a]++;
    in[b]++;
  }

  ll ans = 0;
  for (int i = 1; i <= n; i++) ans += max(0, out[i] - in[i]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
