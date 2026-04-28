#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN];

void solve() {
  int N, x, ans = 0; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) cin >> x, A[i] -= x;
  for (int i = 0; i < N; ++i) ans += A[i] <= 0;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
