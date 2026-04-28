#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;
ll N;

ll C(int lev) {
  if (lev >= 60) return INF + 1;
  return 1LL << lev;
}

vector<int> r(int i, ll k) {
  if (i == 1) return {1};

  if (C(i - 2) < k) {
    auto p = r(i - 1, k - C(i - 2));
    p.insert(p.begin(), i);
    return p;
  }
  else {
    auto p = r(i - 1, k);
    for (auto& x : p) x++;
    p.insert(p.begin(), 1);
    return p;
  }
}

void solve() {
  ll K; cin >> N >> K;
  if (K > C(N - 1)) return cout << "-1\n", void();

  for (int e : r(N, K)) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
