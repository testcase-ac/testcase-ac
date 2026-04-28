#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  int C[26]{};
  for (int i = 0; i < N / 2; ++i) {
    char u = S[i], v = S[N - i - 1];
    C[u - 'a'] ^= 1;
    C[v - 'a'] ^= 1;
  }

  bool f = true;
  for (int i = 0; i < 26; ++i) f &= C[i] == 0;
  cout << (f ? "Yes" : "No") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
