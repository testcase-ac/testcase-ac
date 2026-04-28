#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N; cin >> N;

  int sum = 0, min_odd = INF;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    sum += x;
    if (x & 1) min_odd = min(min_odd, x);
  }

  if (sum & 1) sum -= min_odd;
  cout << sum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
