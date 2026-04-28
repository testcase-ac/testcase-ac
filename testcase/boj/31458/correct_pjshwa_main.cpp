#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;

  int f[2]{};
  while (S.back() == '!') f[1] = 1, S.pop_back();
  reverse(S.begin(), S.end());
  while (S.back() == '!') f[0] ^= 1, S.pop_back();
  assert(S == "0" || S == "1");

  int v = S[0] - '0';
  if (f[1]) v = 1;
  v ^= f[0];
  cout << v << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
