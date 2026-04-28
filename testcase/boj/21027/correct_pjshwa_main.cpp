#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  int u = 0, x;
  for (int i = 0; i < N; i++) {
    cin >> x; u ^= x;
  }

  if (u & 1) cout << "John\n";
  else cout << "Preston\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
