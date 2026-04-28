#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN], B[MAXN], U[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> B[i];
  for (int i = 1; i < N; ++i) {
    if (B[i] > B[i - 1]) {
      A[i] = B[i - 1];
      U[B[i - 1]] = 1;
    }
  }
  int v = 1;
  for (int i = 0; i < N; ++i) {
    if (A[i]) continue;
    while (U[v]) ++v;
    A[i] = v++;
  }

  set<int> S; int mex = 1;
  for (int i = 0; i < N; ++i) {
    S.insert(A[i]);
    while (S.count(mex)) ++mex;
    if (mex != B[i]) return cout << "No\n", void();
  }
  cout << "Yes\n";
  for (int i = 0; i < N; ++i) cout << A[i] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
