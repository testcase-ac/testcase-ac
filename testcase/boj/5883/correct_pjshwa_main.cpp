#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int get_max_streak(vector<int>& v) {
  int n = v.size(), max_streak = 0, streak = 0, last = -1;
  for (int i = 0; i < n; ++i) {
    if (v[i] == last) ++streak;
    else {
      max_streak = max(max_streak, streak);
      streak = 1;
      last = v[i];
    }
  }
  return max(max_streak, streak);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; ++i) cin >> A[i];

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    vector<int> B; int v = A[i];
    for (int j = 0; j < N; ++j) {
      if (A[j] != v) B.push_back(A[j]);
    }
    ans = max(ans, get_max_streak(B));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
