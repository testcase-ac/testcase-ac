#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int r, s, p; cin >> r >> s >> p;

  vector<int> order;
  for (int i = 0; i < p; i++) {
    int ki, kj; cin >> ki >> kj;

    int dist = r - ki + 1;
    if (kj <= s) dist += (s - kj + 1);
    else dist += (kj - s);
    order.push_back(dist);
  }

  sort(order.begin(), order.end());
  for (int i = 1; i < p; ++i) {
    order[i] = max(order[i], order[i - 1] + 1);
  }
  cout << order.back() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
