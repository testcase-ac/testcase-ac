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

  vector<int> A(N); int all = 0;
  for (int i = 0; i < N; i++) cin >> A[i], all += A[i];

  int ans = all, run = 0;
  for (int i = 0; i < N; i++) {
    run += A[i];
    ans = min(ans, all - run + i + 1 - run);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
