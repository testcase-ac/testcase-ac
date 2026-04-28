#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  int i = 0, nom = 0, den = 0;
  while (i < N) {
    if (S[i] == 'A') nom += 8;
    if (S[i] == 'B') nom += 6;
    if (S[i] == 'C') nom += 4;
    if (S[i] == 'D') nom += 2;

    if (i < N - 1 && S[i + 1] == '+') {
      nom += 1; i += 1;
    }
    i += 1;
    den += 2;
  }

  double ans = (double)nom / den;
  cout << fixed << setprecision(10) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
