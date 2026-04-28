#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 6e5;
ll A[MAX + 1], B[MAX + 1];

void solve() {
  int N, K, L; cin >> N >> K >> L;
  for (int i = 1; i <= N; i++) cin >> A[i];

  for (int i = 0; i < K; i++) {
    int x; cin >> x;
    B[x]++; B[x + L]--;
  }
  for (int i = 1; i <= N; i++) B[i] += B[i - 1];

  sort(A + 1, A + N + 1);
  sort(B + 1, B + N + 1);

  ll ans = 0;
  for (int i = 1; i <= N; i++) {
    int m = A[i], c = B[i];
    while (c--) {
      m /= 2;
      if (m == 0) break;
    }
    ans += m;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
