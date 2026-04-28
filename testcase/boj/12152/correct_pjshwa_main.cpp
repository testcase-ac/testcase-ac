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

  int C, D, V; cin >> C >> D >> V;
  vector<ll> A(D);
  for (ll& x : A) cin >> x;
  A.push_back(V + 1);
  sort(A.begin(), A.end());

  ll sum = 0, ans = 0;
  for (ll& x : A) {
    while (x > sum + 1) {
      ++ans;
      sum += (sum + 1) * C;
    }
    sum += x * C;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
