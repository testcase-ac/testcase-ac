#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

// int f(int n) {
//   vector<int> V(n);
//   iota(V.begin(), V.end(), 1);

//   for (int i = 0; i < n; ++i) {
//     int x = V[i];

//     int l = 0, r = n - 1, cnt = 0;
//     while (l <= r) {
//       ++cnt;

//       int mid = (l + r) / 2;
//       if (V[mid] == x) break;
//       else if (V[mid] < x) l = mid + 1;
//       else r = mid - 1;
//     }

//     cout << "i = " << i << ", x = " << x << ", cnt = " << cnt << "\n";
//   }
// }

map<ll, ll> dp;
ll g(ll N) {
  if (N == 0) return 0;
  if (dp.count(N)) return dp[N];

  ll H = N / 2;
  ll ret = g(H) + g(N - H - 1) + N;
  return dp[N] = ret;
}

ll N, tc;
void solve() {
  cout << "Case " << ++tc << ": " << g(N) << "\n";
}

int main() {
  fast_io();
  while (cin >> N) solve();
}
