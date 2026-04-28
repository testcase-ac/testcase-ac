#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int W, N; cin >> W >> N;
  vector<int> A;
  for (int i = 0; i < W; ++i) {
    int x; cin >> x;
    A.push_back(x);
    A.push_back(x - N);
    A.push_back(x + N);
  }
  sort(A.begin(), A.end());

  vector<ll> pre(3 * W + 1, 0);
  for (int i = 0; i < 3 * W; ++i) {
    pre[i + 1] = pre[i] + A[i];
  }
  auto sum_range = [&](int l, int r) {
    return pre[r + 1] - pre[l];
  };

  ll ans = INF; int p = 0;
  for (int i = W; i < 2 * W; ++i) {
    while (A[i] - A[p] > N / 2) ++p;

    ll lsum = (ll)(i - p) * A[i] - sum_range(p, i - 1);
    ll rsum = -(ll)(W - (i - p)) * A[i] + sum_range(i, p + W - 1);
    ans = min(ans, lsum + rsum);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
