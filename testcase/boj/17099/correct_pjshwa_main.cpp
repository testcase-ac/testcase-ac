#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  vector<tii> A(N);
  for (int i = 0; i < N; i++) {
    int s, e, c;
    cin >> s >> e >> c;
    A[i] = {s, e, c};
  }
  sort(A.begin(), A.end(), [](tii a, tii b) {
    return get<1>(a) < get<1>(b);
  });

  map<int, int> d;
  for (int i = 0; i < N; i++) {
    auto [s, e, c] = A[i];
    if (!d.count(e)) {
      auto it = d.upper_bound(e);
      if (it != d.begin()) {
        it--;
        d[e] = it->second;
      }
    }

    auto it = d.upper_bound(s - 1);
    if (it == d.begin()) d[e] = max(d[e], c);
    else {
      it--;
      int val = it->second + c;
      d[e] = max(d[e], val);
    }
  }

  int ans = 0;
  for (auto [e, c] : d) ans = max(ans, c);
  cout << ans << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
