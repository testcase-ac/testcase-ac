#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  bool dec = false;
  for (int i = 1; i < N; i++) {
    if (S[i] < S[i - 1]) dec = true;
    if (dec && S[i] > S[i - 1]) {
      char c = S[i - 1];
      for (int j = i; j < N; j++) S[j] = c;
      break;
    }
  }
  cout << S << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
