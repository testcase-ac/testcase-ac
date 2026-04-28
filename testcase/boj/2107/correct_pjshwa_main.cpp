#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
  int N; cin >> N;

  vector<pii> A;
  for (int i = 0; i < N; i++) {
    int s, e; cin >> s >> e;
    A.emplace_back(s, e);
  }
  sort(A.begin(), A.end(), [](const pii& a, const pii& b) {
    return a.second < b.second;
  });

  ordered_set<ll> P; int ans = 0;
  for (auto& [s, e] : A) {
    int p = P.order_of_key(s);
    ans = max(ans, (int)P.size() - p);
    P.insert(s);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
