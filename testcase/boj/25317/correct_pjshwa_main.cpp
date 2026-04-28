#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template <typename T>
using ordered_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int sgn(ll x) {
  if (x > 0) return 1;
  if (x < 0) return -1;
  return 0;
}

void solve() {
  int Q;
  cin >> Q;

  int k = 1;
  ordered_multiset<ll> LP;
  set<ll> exact;

  while (Q--) {
    int op;
    cin >> op;

    if (op == 1) {
      ll a, b;
      cin >> a >> b;

      if (a == 0) k *= sgn(b);
      else {
        k *= sgn(a);

        ll z = b / a;
        if (b % a == 0) exact.insert(z);
        else if (b < 0 != a < 0) z--;
        LP.insert(z);
      }
    }
    if (op == 2) {
      ll x;
      cin >> x;

      int res = k;
      if (exact.count(-x)) res *= 0;

      int pz = LP.order_of_key(-x);
      if (pz & 1) res *= -1;

      if (res > 0) cout << "+\n";
      else if (res == 0) cout << "0\n";
      else cout << "-\n";
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
