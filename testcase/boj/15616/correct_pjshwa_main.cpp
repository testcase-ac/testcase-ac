#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e6;
ll C[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    ++C[x];
  }

  ll ans = 0;
  for (int i = 1; i <= MAXN; ++i) {
    ans += C[i] * (C[i] - 1);
    for (int j = i * 2; j <= MAXN; j += i) ans += C[i] * C[j];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
