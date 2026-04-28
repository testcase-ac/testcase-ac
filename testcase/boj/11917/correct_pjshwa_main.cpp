#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXM = 1e6 + 1e5;
int A[MAXM + 1];

void solve() {
  int N; cin >> N;

  set<int> U;
  for (int i = 1; i <= N; ++i) cin >> A[i], U.insert(A[i]);
  for (int i = N + 1; i <= MAXM; ++i) {
    A[i] = U.size();
    U.insert(A[i]);
  }

  int M; cin >> M;
  if (M > MAXM) cout << A[MAXM] + (M - MAXM) * (A[MAXM] - A[MAXM - 1]) << '\n';
  else cout << A[M] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
