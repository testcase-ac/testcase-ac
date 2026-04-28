#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 3e5;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < 3 * N; ++i) cin >> A[i];
  sort(A, A + 3 * N);

  cout << A[N] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
