#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int A[MAX + 1];

void solve() {
  int N;
  cin >> N;

  int S = 0;
  for (int i = 1; i <= N; i++) cin >> A[i], S += A[i];

  sort(A + 1, A + N + 1);

  int ans;
  if (2 * A[N] > S) ans = A[N];
  else ans = (S + 1) / 2;

  if (ans > 1440) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
