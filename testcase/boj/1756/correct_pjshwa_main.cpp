#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int D, N; cin >> D >> N;

  vector<int> A(D); stack<int> S;
  for (int i = 0; i < D; i++) {
    cin >> A[i];
    if (i) A[i] = min(A[i], A[i - 1]);
    S.push(A[i]);
  }

  int ans;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    while (!S.empty() && S.top() < x) S.pop();

    if (S.empty()) return cout << "0\n", void();
    ans = S.size();
    S.pop();
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
