#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;
  vector<pii> A(N);
  for (auto &[x, y] : A) cin >> x >> y;
  sort(A.begin(), A.end());

  int acc = 0, off = 0;
  for (auto &[x, y] : A) {
    acc += y;

    int pre = x / 7 * 5 + min(5, x % 7);
    if (pre + x < acc) return cout << "-1\n", void();
    if (acc - (pre + off) > 0) off = acc - pre;
  }

  cout << off << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
