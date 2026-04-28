#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  deque<int> dq;
  for (int i = 1; i <= N; i++) dq.push_back(i);

  while (dq.size() >= 2) {
    cout << dq.back() << ' '; dq.pop_back();
    cout << dq.front() << ' '; dq.pop_front();
  }

  if (dq.size() == 1) cout << dq.front() << '\n';
  else cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
