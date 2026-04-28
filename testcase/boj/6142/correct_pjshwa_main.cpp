#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  vector<pii> A, B;
  for (int i = 0; i < N; ++i) {
    int a, b; cin >> a >> b;
    A.emplace_back(a, b);
  }
  for (int i = 0; i < M; ++i) {
    int a, b; cin >> a >> b;
    B.emplace_back(a, b);
  }
  sort(A.begin(), A.end(), [](const pii &a, const pii &b) {
    auto [a1, a2] = a; auto [b1, b2] = b;
    if (a2 == b2) return a1 < b1;
    return a2 > b2;
  });
  sort(B.begin(), B.end(), [](const pii &a, const pii &b) {
    auto [a1, a2] = a; auto [b1, b2] = b;
    if (a2 == b2) return a1 < b1;
    return a2 > b2;
  });

  multiset<int> S; ll i = 0, ans = 0;
  for (auto& [a, b] : A) {
    while (i < M && B[i].second >= b) S.insert(B[i++].first);

    auto it = S.lower_bound(a);
    if (it == S.end()) return cout << "-1\n", void();
    ans += *it; S.erase(it);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
