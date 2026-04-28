#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, k; string s; cin >> n >> k >> s;

  int z = s.size();
  if (n * k + k - 1 > z) return cout << "-1\n", void();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
