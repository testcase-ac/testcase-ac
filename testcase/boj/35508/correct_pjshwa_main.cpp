#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N, D, ans = 0; cin >> N >> D;

  vector<tuple<int, int, int>> O;
  for (int i = 0; i < N; ++i) {
    int t, a, b; cin >> t >> a >> b;
    ans = max(ans, a + b);
    O.emplace_back(t, a, b);
  }
  sort(O.begin(), O.end());
  for (int i = 1; i < N; ++i) {
    auto& [t2, a2, b2] = O[i];
    b2 = max(b2, get<2>(O[i - 1]));
  }
  for (auto& [t, a, b] : O) {
    auto it = upper_bound(O.begin(), O.end(), make_tuple(D - t, INF, INF));
    if (it != O.begin()) ans = max(ans, a + get<2>(*prev(it)));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
