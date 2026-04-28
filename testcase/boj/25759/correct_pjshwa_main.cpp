#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
ll d[MAX + 1];
bool L[MAX + 1];

void solve() {
  int N;
  cin >> N;

  ll ans = 0;
  for (int i = 1; i <= N; i++) {
    int x;
    cin >> x;

    for (int p = 1; p <= MAX; p++) {
      if (!L[p]) continue;
      d[x] = max(d[x], d[p] + (x - p) * (x - p));
    }
    L[x] = true;
    ans = max(ans, d[x]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
