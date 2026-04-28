#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  queue<int> q; int L;
  for (int i = 0; i < N; ++i) {
    cin >> L; q.push(L);
  }

  L += K + 1; int ans = 0;
  for (int i = 1; i <= L; ++i) {
    if (q.empty()) break;

    if (q.front() + K == i) {
      ++ans;
      while (!q.empty() && q.front() <= i) q.pop();
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
