#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Data Set " << ++tc << ":\n";

  int N; cin >> N;
  int A[N];
  for (int i = 0; i < N; ++i) cin >> A[i];
  if (N == 1) return cout << "Possible\n", void();

  deque<int> dq;
  for (int i = 1; i < N; ++i) dq.push_back(A[i]);
  sort(dq.begin(), dq.end());

  int ok = 1, val = A[0] + dq.back() / 2, f = 1;
  while (dq.size() >= 2) {
    int cur = (dq.front() + dq.back()) / 2;
    if (cur > val) ok = 0;
    if (f) dq.pop_back();
    else dq.pop_front();
    f ^= 1;
  }
  cout << (ok ? "Possible" : "Impossible") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) {
    solve();
    if (t) cout << '\n';
  }
}
