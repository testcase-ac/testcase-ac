#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  deque<int> dq;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    dq.push_back(x);
  }
  sort(dq.begin(), dq.end());

  ll ans1 = 0, ans2 = 0;
  while (!dq.empty()) {
    if (!dq.empty()) {
      ans1 += dq.back();
      dq.pop_back();
    }
    if (!dq.empty()) {
      ans2 += dq.front();
      dq.pop_front();
    }
  }
  cout << ans2 << ' ' << ans1 << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
