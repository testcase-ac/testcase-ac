#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, l = -1; string S; cin >> N >> S;
  int j = 0; string T = "PAUL";
  for (int i = 0; i < N; ++i) {
    if (j < 4 && S[i] == T[j]) {
      if ((i - l) % 2 == 0) return cout << "NO\n", void();
      l = i; ++j;
    }
  }
  if (j < 4 || (N - l) % 2 == 0) cout << "NO\n";
  else cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
