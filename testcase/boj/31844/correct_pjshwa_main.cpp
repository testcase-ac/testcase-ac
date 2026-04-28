#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  int ri, bi, gi;
  for (int i = 0; i < N; ++i) {
    if (S[i] == '@') ri = i;
    if (S[i] == '#') bi = i;
    if (S[i] == '!') gi = i;
  }

  if (bi >= min(ri, gi) && bi <= max(ri, gi)) cout << abs(ri - gi) - 1 << '\n';
  else cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
