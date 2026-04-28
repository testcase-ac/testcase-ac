#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;

void solve() {
  string S; cin >> S;
  S.erase(remove(S.begin(), S.end(), '.'), S.end());
  ll N = stoll(S);

  ll ans = INF;
  for (int bc = 0; bc < 9; ++bc) for (int cc = 0; cc < 2; ++cc) for (int dc = 0; dc < 40; ++dc) {
    ll sum = bc * 70 + cc * 45 - dc * 20;
    if (sum > N) continue;

    ll rem = N - sum;
    if (rem % 90) continue;

    ans = min(ans, rem / 90 + bc + cc + dc);
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
