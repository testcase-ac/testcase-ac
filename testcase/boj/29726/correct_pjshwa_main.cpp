#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N, M; cin >> N >> M;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  priority_queue<int, vector<int>, greater<int>> pre;

  int ans = -INF;
  for (int i = N - M - 1; i < N; ++i) {
    pre.push(A[i - (N - M - 1)]);
    ans = max(ans, A[i] - pre.top());
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
