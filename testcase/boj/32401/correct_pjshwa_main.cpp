#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  int ans = 0;
  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    if (S[i] != 'A' || S[j] != 'A') continue;
    int acnt = 0, ncnt = 0;
    for (int k = i; k <= j; ++k) {
      if (S[k] == 'A') ++acnt;
      if (S[k] == 'N') ++ncnt;
    }
    ans += acnt == 2 && ncnt == 1;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
