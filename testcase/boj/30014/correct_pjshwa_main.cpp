#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N, greater<int>());

  deque<int> dq;
  dq.push_back(A[0]);

  int ans = 0;
  for (int i = 1; i < N; ++i) {
    if (i & 1) {
      ans += dq.front() * A[i];
      dq.push_front(A[i]);
    }
    else {
      ans += dq.back() * A[i];
      dq.push_back(A[i]);
    }
  }
  ans += dq.front() * dq.back();

  cout << ans << "\n";
  for (int e : dq) cout << e << " ";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
