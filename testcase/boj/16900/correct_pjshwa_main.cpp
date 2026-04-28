#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; ll K; cin >> S >> K;

  int N = S.size();
  vector<int> pi(N);
  for (int i = 1, j = 0; i < N; i++) {
    while (j && S[i] != S[j]) j = pi[j - 1];
    if (S[i] == S[j]) pi[i] = ++j;
  }
  ll ans = N + (K - 1) * (N - pi.back());
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
