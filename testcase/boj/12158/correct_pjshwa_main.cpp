#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; cin >> N;
  vector<pll> A;
  for (int i = 0; i < N; ++i) {
    ll d, h, m; cin >> d >> h >> m;
    for (int j = 0; j < h; ++j) A.emplace_back((m + j) * (360 - d), m + j);
  }
  N = A.size();
  sort(A.begin(), A.end());

  ll ans = N;
  for (int i = 0; i < N; ++i) {
    ll pre = 0, dur = A[i].first;
    for (int j = 0; j < i; ++j) {
      ll pdur = A[j].first;
      if (dur > pdur) {
        ll cnt = (dur - pdur) / (360 * A[j].second);
        pre += cnt;
      }
    }
    ans = min(ans, pre + N - i - 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
