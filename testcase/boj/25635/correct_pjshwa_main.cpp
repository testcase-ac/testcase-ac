#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
ll A[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N);

  ll lsum = 0, mx = A[N - 1];
  for (int i = 0; i < N - 1; ++i) lsum += A[i];

  if (lsum < mx) cout << 2 * lsum + 1 << '\n';
  else cout << lsum + mx << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
