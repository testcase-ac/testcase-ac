#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;
  vector<pii> A;
  for (int i = 1; i <= M; i++) {
    int x; cin >> x;
    A.push_back({x, i});
  }
  sort(A.begin(), A.end());

  ll acc = 0; vector<int> ans;
  while (acc < N) {
    auto [x, i] = A.back(); A.pop_back();
    if (x > 2 * N) continue;
    acc += x; ans.push_back(i);
  }

  cout << ans.size() << '\n';
  for (int e : ans) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
