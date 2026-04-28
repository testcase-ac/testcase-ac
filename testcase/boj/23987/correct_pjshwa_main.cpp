#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; string S; cin >> N >> S;

  vector<int> P(N + 1);
  for (int i = 1; i <= N; ++i) {
    P[i] = P[i - 1] + (S[i - 1] - '0');
  }

  int W = (N + 1) / 2, ans = 0;
  for (int i = 0; i <= N - W; ++i) ans = max(ans, P[i + W] - P[i]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
