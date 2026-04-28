#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N; cin >> N;
  for (ll i = N - 400; i <= N; i++) {
    if (i < 1) continue;

    string s = to_string(i);
    ll dsum = 0;
    for (char c : s) dsum += c - '0';

    if (i + dsum == N) return cout << i << '\n', void();
  }
  cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
