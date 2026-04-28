#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 30;
ll d[MAX + 1];

void solve() {
  int N;
  cin >> N;

  d[0] = d[1] = 1;
  for (int i = 2; i <= N; i++) {
    d[i] = d[i - 1] + 2 * d[i - 2];
  }

  ll ans;
  if (N & 1) ans = (d[N] + d[N / 2]) / 2;
  else ans = (d[N] + d[N / 2] + 2 * d[(N - 2) / 2]) / 2;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
