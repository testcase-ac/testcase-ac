#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, A, B; cin >> N >> A >> B;
  N = 8 - N;
  A = min(A, 66); B = min(B, 130);
  int mneed = (66 - A - 1) / 3 + 1, wneed = (130 - B - 1) / 3 + 1;

  int X[10], Y[10];
  for (int i = 0; i < 10; i++) cin >> X[i] >> Y[i];

  for (int i = 0; i < N; i++) {
    int m = X[i], w = min(6, X[i] + Y[i]);
    mneed -= m; wneed -= w;
  }

  if (mneed <= 0 && wneed <= 0) cout << "Nice\n";
  else cout << "Nae ga wae\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
