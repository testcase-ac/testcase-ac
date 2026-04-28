#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5000;
int A[MAX];

void solve() {
  int N, K;
  cin >> N >> K;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N);
  reverse(A, A + N);

  int ans = 0;
  for (int i = 0; i < K; i++) {
    ans += A[i] - i;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
