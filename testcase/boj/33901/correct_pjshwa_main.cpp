#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6, MAXV = 2e5;
int A[MAXN], V[MAXV + 1];

void solve() {
  int N, M, K; cin >> N >> M >> K;

  ll ans = 0;
  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    if (i > M) --V[A[i - M - 1]];
    ans += V[A[i] ^ K];
    ++V[A[i]];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
