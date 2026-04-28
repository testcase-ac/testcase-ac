#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int A, B, K; cin >> A >> B >> K;

  vector<int> factors_b;
  for (int f = 1; f <= B; ++f) {
    if (B % f == 0) factors_b.push_back(f);
  }

  vector<int> candidates;
  for (int f : factors_b) {
    if (f % A == 0) candidates.push_back(f);
  }

  if ((int)candidates.size() < K) cout << "-1\n";
  else {
    for (int j = 0; j < K - 1; ++j) cout << candidates[j] << ' ';
    cout << candidates.back() << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
