#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S;
  cin >> N >> S;

  int ans = N, cur = 0;
  for (int i = N - 1; i >= 0; i--) {
    if (S[i] == 's') cur++;
    else cur--;

    if (cur == 0) ans = min(ans, i);
  }

  cout << S.substr(ans) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
