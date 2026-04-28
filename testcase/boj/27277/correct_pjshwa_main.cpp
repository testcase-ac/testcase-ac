#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  deque<int> dq;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    dq.push_back(x);
  }
  sort(dq.begin(), dq.end());

  vector<int> A;
  while (dq.size() >= 2) {
    A.push_back(dq.back()); dq.pop_back();
    A.push_back(dq.front()); dq.pop_front();
  }
  if (dq.size()) A.push_back(dq.front());

  int ans = A[0];
  for (int i = 1; i < N; i++) ans += max(0, A[i] - A[i - 1]);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
