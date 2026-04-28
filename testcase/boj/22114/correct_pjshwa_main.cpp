#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K;
  cin >> N >> K;

  vector<int> P; int streak = 1, x;
  for (int i = 0; i < N - 1; i++) {
    cin >> x;
    if (x <= K) streak++;
    else {
      P.push_back(streak);
      streak = 1;
    }
  }
  P.push_back(streak);

  int ans = P[0];
  for (int i = 1; i < P.size(); i++) ans = max(ans, P[i] + P[i - 1]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
