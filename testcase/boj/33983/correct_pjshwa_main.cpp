#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;
  if (N % 3) return cout << "mix\n", void();

  int T = N / 3, ocnt = 0, hcnt;
  for (char c : S) if (c == 'O') ++ocnt;
  if (ocnt != T) return cout << "mix\n", void();

  hcnt = 0;
  for (int i = 0; i < N; ++i) {
    if (S[i] == 'H') ++hcnt;
    else --hcnt;
    if (hcnt < 0) return cout << "mix\n", void();
  }

  hcnt = 0;
  for (int i = N - 1; i >= 0; --i) {
    if (S[i] == 'H') ++hcnt;
    else --hcnt;
    if (hcnt < 0) return cout << "mix\n", void();
  }

  cout << "pure\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
