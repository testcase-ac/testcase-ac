#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int ans = (N & 1) ^ 1;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    ans ^= x;
  }
  if (ans) cout << "eerste\n";
  else cout << "tweede\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
