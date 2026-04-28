#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

const int MAXN = 1e6, BIAS = 5e5;
ordered_multiset<ll> L[MAXN + 1];
int C[MAXN + 1], W[MAXN + 1];

void insert(int i, ll x) {
  L[i + BIAS].insert(x);
}

int order_of_key(int i, ll x) {
  return L[i + BIAS].order_of_key(x);
}

void solve() {
  int N, K; cin >> N >> K;
  for (int i = -N; i <= N; ++i) L[i + BIAS].clear();

  for (int i = 1; i <= N; ++i) {
    cin >> C[i];
    C[i] == 1 ? C[i] = 1 : C[i] = -1;
  }
  for (int i = 1; i <= N; ++i) cin >> W[i];

  insert(0, 0); ll run = 0, dt = 0, ans = 0;
  for (int i = 1; i <= N; ++i) {
    dt += C[i];
    run += C[i] * W[i];

    int lb = order_of_key(dt, run - K);
    int ub = order_of_key(dt, run + K + 1);
    ans += ub - lb;

    insert(dt, run);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
