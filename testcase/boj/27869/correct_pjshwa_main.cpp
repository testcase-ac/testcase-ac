#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
ll P[MAX + 1];

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 1; i <= N; i++) cin >> P[i], P[i] += P[i - 1];

  set<int> stops;
  while (Q--) {
    int op; cin >> op;

    if (op == 1) {
      int x; cin >> x;
      stops.insert(x);
    }
    if (op == 2) {
      int s, e; cin >> s >> e;

      auto it = stops.lower_bound(e);
      if (it != stops.begin()) {
        it--;
        int x = *it;
        s = max(s, x + 1);
      }
      cout << P[e] - P[s - 1] << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
