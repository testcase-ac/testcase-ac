#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int A[MAX];

void solve() {
  int N, K;
  cin >> N >> K;

  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N);

  int ans = 0;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < N; i++) {
    if (i + K - 1 < N) pq.push({A[i + K - 1] - A[i], i + K});
    while (pq.top().second <= i) pq.pop();
    ans = max(ans, pq.top().first);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
