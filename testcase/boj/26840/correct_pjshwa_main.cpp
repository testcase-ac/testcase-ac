#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int A[MAX];

void solve() {
  int B, Q; cin >> B >> Q;

  // number divisible by B - 1 iff digit sum is divisible by B - 1
  ll rem = 0;
  for (int i = 0; i < B; ++i) {
    cin >> A[i];
    ll u = (ll)i * A[i];
    rem = (rem + u) % (B - 1);
  }
  if (rem > 0) --A[rem];

  vector<ll> pre(B); pre[0] = A[0];
  for (int i = 1; i < B; ++i) pre[i] = pre[i - 1] + A[i];

  while (Q--) {
    ll K; cin >> K;
    auto it = upper_bound(pre.begin(), pre.end(), K);
    if (it == pre.end()) cout << "-1\n";
    else cout << it - pre.begin() << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
