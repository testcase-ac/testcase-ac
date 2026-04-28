#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string S, K;
  getline(cin, S);
  cin >> K;

  for (int i = 0; i < S.size(); i++) {
    if (S[i] == ' ') {
      cout << ' ';
      continue;
    }

    int d = K[i % K.size()] - 'a' + 1;
    int p = S[i] - 'a';
    p -= d;
    if (p < 0) p += 26;

    cout << (char)(p + 'a');
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
