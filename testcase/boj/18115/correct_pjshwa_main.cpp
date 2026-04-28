#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<int> C(N);
  for (int i = 0; i < N; ++i) cin >> C[i];

  deque<int> dq;
  for (int i = N - 1; i >= 0; --i) {
    int cur = N - i;
    if (C[i] == 1) dq.push_front(cur);
    if (C[i] == 2) {
      int tmp = dq.front(); dq.pop_front();
      dq.push_front(cur);
      dq.push_front(tmp);
    }
    if (C[i] == 3) dq.push_back(cur);
  }

  for (int i = 0; i < N; ++i) cout << dq[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
