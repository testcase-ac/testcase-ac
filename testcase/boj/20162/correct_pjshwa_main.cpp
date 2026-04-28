#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int A[MAX], d[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  d[0] = A[0]; int ans = d[0];
  for (int i = 1; i < N; i++) {
    d[i] = A[i];
    for (int j = 0; j < i; j++) {
      if (A[j] >= A[i]) continue;
      d[i] = max(d[i], d[j] + A[i]);
    }
    ans = max(ans, d[i]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
