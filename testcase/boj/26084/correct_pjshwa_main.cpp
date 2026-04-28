#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int T[26]{};
  int U[26]{};

  string S;
  cin >> S;
  for (char& c : S) T[c - 'A']++;

  int M;
  cin >> M;
  while (M--) {
    string S;
    cin >> S;
    U[S[0] - 'A']++;
  }

  ll ans = 1;
  for (int i = 0; i < 26; i++) {
    // if (U[i] < T[i]) return cout << "0\n", void();

    for (int j = 1; j <= T[i]; j++) {
      ans *= (U[i] + 1 - j);
      ans /= j;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
