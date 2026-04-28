#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N; cin >> N;

  ll C[10]{}, base = N / 10;
  for (int i = 1; i <= N % 10; i += 2) {
    ll w = 10 * base + i;
    string S = to_string(w);
    for (char c : S) C[c - '0'] += 1;
  }
  N = base - 1;
  for (int i = 1; i <= 9; i += 2) C[i] += N;

  ll mul = 5;
  while (1) {
    cout << "C = ";
    for (int i = 0; i <= 9; ++i) cout << C[i] << " \n"[i == 9];
    cout << "N = " << N << ", mul = " << mul << "\n";
    ll base = N / 10;
    for (int i = 0; i <= N % 10; ++i) {
      ll w = 10 * base + i;
      if (w == 0) continue;
      cout << "w = " << w << "\n";

      string S = to_string(w);
      for (char c : S) C[c - '0'] += mul;
    }
    N = base - 1;
    if (N <= 0) break;
    for (int i = 0; i <= 9; ++i) C[i] += N * mul;
    mul *= 10;
  }

  for (int i = 0; i < 10; ++i) cout << C[i] << " \n"[i == 9];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
