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

template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

void solve() {
  int Q; cin >> Q;

  ordered_multiset<ll> D, X;
  set<pii> E;

  while (Q--) {
    int op; cin >> op;
    if (op == 1) {
      ll x; cin >> x;
      ll d = x * x;
      int xrng = X.order_of_key(x) - X.order_of_key(-x + 1);
      cout << xrng - D.order_of_key(d + 1) << '\n';
    }
    else {
      ll x, y; cin >> x >> y;
      ll d = x * x + y * y;
      if (E.count({x, y})) {
        E.erase({x, y});
        D.erase(D.find_by_order(D.order_of_key(d)));
        X.erase(X.find_by_order(X.order_of_key(x)));
      }
      else {
        E.insert({x, y});
        D.insert(d);
        X.insert(x);
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
