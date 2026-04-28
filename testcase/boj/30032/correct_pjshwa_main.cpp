#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

char flip(char o, int D) {
  if (D == 1) {
    if (o == 'd') return 'q';
    if (o == 'b') return 'p';
    if (o == 'q') return 'd';
    if (o == 'p') return 'b';
  }
  else {
    if (o == 'd') return 'b';
    if (o == 'b') return 'd';
    if (o == 'q') return 'p';
    if (o == 'p') return 'q';
  }
}

void solve() {
  int N, D; cin >> N >> D;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    for (char c : S) cout << flip(c, D);
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
