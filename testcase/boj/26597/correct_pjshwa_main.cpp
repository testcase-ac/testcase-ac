#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;

void solve() {
  ll lb = -INF, ub = INF;

  int Q;
  cin >> Q;
  vector<pair<ll, string>> qs(Q);

  for (int i = 0; i < Q; i++) {
    ll u; string op;
    cin >> u >> op;
    qs[i] = {u, op};

    if (op == "^") lb = max(lb, u + 1);
    if (op == "v") ub = min(ub, u - 1);

    if (lb > ub) return cout << "Paradox!\n" << i + 1 << '\n', void();
  }

  lb = -INF, ub = INF;
  for (int i = 0; i < Q; i++) {
    auto [u, op] = qs[i];

    if (op == "^") lb = max(lb, u + 1);
    if (op == "v") ub = min(ub, u - 1);

    if (lb == ub) return cout << "I got it!\n" << i + 1 << '\n', void();
  }

  cout << "Hmm...\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
