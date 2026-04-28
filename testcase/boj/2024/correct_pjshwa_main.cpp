#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int M; cin >> M;

  vector<pii> A; int L, R;
  while (cin >> L >> R) A.emplace_back(max(0, L), R);
  sort(A.begin(), A.end());

  priority_queue<int> pq; int N = A.size(), lx = 0, li = 0;
  while (li < N && A[li].first == lx) pq.push(A[li++].second);

  int ans = 0;
  while (lx < M) {
    if (pq.empty()) return cout << "0\n", void();

    lx = max(lx, pq.top()); pq.pop(); ++ans;
    while (li < N && A[li].first <= lx) pq.push(A[li++].second);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
