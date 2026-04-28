#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, S[6], T, P;
  cin >> N;
  for (int i = 0; i < 6; ++i) cin >> S[i];
  cin >> T >> P;

  int tans = 0;
  for (int i = 0; i < 6; ++i) tans += (S[i] + T - 1) / T;
  cout << tans << '\n' << N / P << ' ' << N % P << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
