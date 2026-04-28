#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A.begin(), A.end());

  set<int> u;
  int ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      int d = A[j] - A[i];
      if (u.count(A[i] - d)) ans++;
    }
    u.insert(A[i]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
