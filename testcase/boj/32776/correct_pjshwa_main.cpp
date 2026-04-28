#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int S, Ma, F, Mb; cin >> S >> Ma >> F >> Mb;
  if (S <= 240 || Ma + F + Mb >= S) cout << "high speed rail\n";
  else cout << "flight\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
