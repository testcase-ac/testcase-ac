#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  vector<pii> A;
  for (int j = 0; j < M; ++j) {
    int a, b; cin >> a >> b;
    A.emplace_back(a, b);
  }
  sort(A.begin(), A.end());

  int j = 0, ans = 0;
  priority_queue<int, vector<int>, greater<int>> pq;

  for (int i = 1; i <= N; ++i) {
    while (j < M && A[j].first <= i) {
      pq.push(A[j].second);
      ++j;
    }
    while (!pq.empty() && pq.top() < i) pq.pop();
    if (!pq.empty()) {
      pq.pop();
      ++ans;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
