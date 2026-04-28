#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  stack<pii> s; ll ans = 0;
  for (int i = 0; i < N; ++i) {
    while (!s.empty() && s.top().first < A[i]) {
      auto [_, j] = s.top(); s.pop();
      ans += i - j + 1;
    }
    s.push({A[i], i});
  }

  while (!s.empty()) s.pop();
  reverse(A.begin(), A.end());
  for (int i = 0; i < N; ++i) {
    while (!s.empty() && s.top().first < A[i]) {
      auto [_, j] = s.top(); s.pop();
      ans += i - j + 1;
    }
    s.push({A[i], i});
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
