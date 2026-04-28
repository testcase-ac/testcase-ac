#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; string S; cin >> N >> K >> S;

  int i = 0, j = N - 1;
  while (K) {
    while (S[i] == 'P') ++i;
    while (S[j] == 'C') --j;
    if (i >= j) break;

    swap(S[i], S[j]);
    --K;
  }

  ll p1 = 0, p2 = 0, ans = 0;
  for (int i = 0; i < N; ++i) {
    if (S[i] == 'C') ans += p2;
    else p2 += p1, ++p1;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
