#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ull N; cin >> N;
  ull h = N / 2;
  cout << h * (N - h) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
