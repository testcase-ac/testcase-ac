#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  deque<int> A;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    A.push_back(x);
  }
  sort(A.begin(), A.end());

  int ans = 0;
  while (M-- && !A.empty()) {
    int x = A.back(); A.pop_back();
    if (x <= 0) break;
    ans += x;

    if (A.empty()) break;
    A.pop_front();
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
