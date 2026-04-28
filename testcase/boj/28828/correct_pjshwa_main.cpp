#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll A[MAXN], B[MAXN];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < M; ++i) cin >> B[i];
  sort(A, A + N, greater<ll>());
  sort(B, B + M, greater<ll>());

  int i = 0, j = 0; long double ans = 1;
  while (1) {
    if (j < M && ans > B[j]) ans /= B[j++];
    else if (i < N) ans *= A[i++];
    else if (j < M) ans /= B[j++];
    else break;
  }
  cout << (ll)ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
