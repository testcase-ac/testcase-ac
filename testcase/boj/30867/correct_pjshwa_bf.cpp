#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int L, N; string S; cin >> L >> N >> S;

  L = S.size();
  for (int i = 0; i < N; ++i) {
    for (int j = 1; j < L; ++j) {
      if (S[j - 1] == 'w' && S[j] == 'h') swap(S[j - 1], S[j]);
    }
  }
  cout << S << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
