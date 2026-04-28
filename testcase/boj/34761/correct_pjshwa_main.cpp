#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 4e5;
int A[MAXN], B[MAXN], V[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i], V[A[i]] = 1;
  for (int i = 0; i < 2 * N; ++i) cin >> B[i];

  for (int i = 0; i < N; ++i) if (A[i] != B[i]) return cout << "NO\n", void();
  for (int i = N; i < 2 * N; ++i) if (!V[B[i]]) return cout << "NO\n", void();
  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
