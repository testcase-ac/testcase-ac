#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S, T; cin >> S >> T;

  int N = S.size();
  for (int f = 1; f <= N; f++) {
    if (N % f) continue;

    vector<int> D(f);
    for (int i = 0; i < f; i++) {
      D[i] = (T[i] - S[i] + 26) % 26;
    }

    bool able = true;
    for (int i = f; i < N; i++) {
      if ((T[i] - S[i] + 26) % 26 != D[i % f]) able = false;
    }
    if (!able) continue;

    for (int i = 0; i < f; i++) {
      D[i] = (D[i] + 25) % 26;
      cout << (char)('A' + D[i]);
    }
    break;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
