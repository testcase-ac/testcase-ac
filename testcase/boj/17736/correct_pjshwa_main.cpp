#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int c2i(char c) {
  if (c == 'J') return 0;
  if (c == 'O') return 1;
  return 2;
}

void solve() {
  int N, C[3]{}, ans = 0; string S; cin >> N >> S;
  map<pair<int, int>, int> D; D[{0, 0}] = -1;
  for (int i = 0; i < N; ++i) {
    ++C[c2i(S[i])];
    pair<int, int> key = {C[0] - C[1], C[0] - C[2]};
    if (D.count(key)) ans = max(ans, i - D[key]);
    else D[key] = i;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
