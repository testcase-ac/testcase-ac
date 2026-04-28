#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, ans = 0; cin >> N >> M;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    for (char c : S) ans ^= (c == '.');
  }
  if (ans) cout << "sewon\n";
  else cout << "pizza\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
