#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  int az = 0, bz = 0;
  for (char c : S) {
    if (c == 'a') az++;
    else bz++;
  }

  int ans = N;
  for (int i = 0; i < N; ++i) {
    int cur = 0;
    for (int j = 0; j < bz; ++j) {
      cur += S[(i + j) % N] == 'a';
    }
    ans = min(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
