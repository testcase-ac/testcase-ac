#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int A[MAX], B[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (A[i] == B[i]) continue;

    ans++;
    for (int j = 0; j < 3; j++) {
      if (i + j >= N) break;
      B[i + j] ^= 1;
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
