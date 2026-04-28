#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, O; cin >> N >> O;
  for (int i = 0; i < N; i++) cin >> O;

  string S; cin >> S;
  reverse(S.begin(), S.end());
  cout << S << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
