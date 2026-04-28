#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  vector<int> A(N), B(M);
  for (int& a : A) cin >> a;
  for (int& b : B) cin >> b;
  sort(B.begin(), B.end());

  vector<int> R(N);
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < N - 1; i++) {
    R[i] = i + 1;
    pq.push({A[i + 1] - A[i], i});
  }

  auto pop_and_put_next = [&]() {
    int i = pq.top().second; pq.pop();
    ++R[i];
    if (R[i] < N) pq.push({A[R[i]] - A[i], i});
  };

  for (int l = 0; l < M; ++l) {
    if (pq.empty() || pq.top().first > B[l]) return cout << "no\n", void();
    else pop_and_put_next();
  }
  cout << "yes\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
