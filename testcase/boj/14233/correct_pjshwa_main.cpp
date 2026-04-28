#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 50000;
int A[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];
  sort(A + 1, A + N + 1);

  int ans = A[1];
  for (int i = 1; i <= N; ++i) {
    ans = min(ans, A[i] / i);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
