#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int t, l; cin >> t >> l;
    if (t < l) return cout << "-1\n", void();
    A.emplace_back(t, l);
  }
  sort(A.begin(), A.end());
  for (int i = 1; i < N; ++i) {
    A[i].second = max(A[i].second, A[i - 1].second);
  }
  for (int i = N - 2; i >= 0; --i) {
    auto [nt, nl] = A[i + 1]; auto [pt, pl] = A[i];
    if (nt - pt < nl - pl) {
      A[i].second = nl - (nt - pt);
    }
  }

  // cout << "A = ";
  // for (auto& p : A) cout << "(" << p.first << "," << p.second << ") ";
  // cout << '\n';

  ll ans = 0;
  for (auto& [t, l] : A) ans += t - l;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
