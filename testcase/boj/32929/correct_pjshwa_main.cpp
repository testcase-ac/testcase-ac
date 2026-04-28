#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int x; cin >> x;
  string S = "";
  if (x % 3 == 0) S.push_back('S');
  if (x % 3 == 1) S.push_back('U');
  if (x % 3 == 2) S.push_back('O');
  cout << S.back() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
