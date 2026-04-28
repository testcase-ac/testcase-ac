#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  string S; cin >> S;
  int N = S.size();
  set<char> U[N];

  for (int i = 0; i < N; i++) {
    for (int d = -1; d <= 1; d++) {
      int j = i + d;
      if (0 <= j && j < N) U[j].insert(S[i]);
    }
  }

  ll ans = 1;
  for (int i = 0; i < N; i++) {
    ans = ans * U[i].size() % MOD;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
