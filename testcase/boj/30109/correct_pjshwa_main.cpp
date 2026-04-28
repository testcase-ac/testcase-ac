#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;
  vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int Li, Ri; cin >> Li >> Ri;
    A.emplace_back(Li, Ri);
  }
  sort(A.begin(), A.end());
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
