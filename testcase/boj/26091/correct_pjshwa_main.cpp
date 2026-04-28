#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N);

  int r = N - 1, ans = 0;
  for (int i = 0; i < N; i++) {
    if (i >= r) break;
    if (A[i] + A[r] >= M) ans++, r--;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
