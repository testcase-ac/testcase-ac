#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000;
int A[MAX], d[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  int ans = 0;
  for (int i = 0; i < N; i++) {
    d[i] = 1;
    for (int j = 0; j < i; j++) {
      if (A[j] < A[i]) d[i] = max(d[i], d[j] + 1);
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
