#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll k, sum, d, p; cin >> k; --k;
  for (sum = 0, d = 1, p = 9;; ++d) {
    if (sum + p * d > k) break;
    sum += p * d;
    if (d % 2 == 0) p *= 10;
  }

  ll pos = (k - sum) / d;
  string S = to_string(p / 9 + pos), T;
  if (d & 1) T = S.substr(0, S.size() - 1);
  else T = S;
  reverse(T.begin(), T.end());
  S += T;

  int w = k - sum - pos * d;
  cout << S[w] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
