#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
ll A[MAXN];

void solve() {
  ll N, sum = 0; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i], sum += A[i];
  sort(A, A + N);

  ll ans = sum;
  for (int i = 0; i < N - 1; ++i) {
    ll a = A[i], b = A[i + 1];
    ans = max(ans, sum - a - b + 2 * a * b);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
