#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

void solve() {
  int N;
  cin >> N;
  vector<pii> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i].second >> A[i].first;
  }
  sort(A.begin(), A.end());
  reverse(A.begin(), A.end());

  int cur = INF;
  for (auto [Si, Ti] : A) {
    if (cur > Si) cur = Si;
    cur -= Ti;
  }

  if (cur < 0) cur = -1;
  cout << cur << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
