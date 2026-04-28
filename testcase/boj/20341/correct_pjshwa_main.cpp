#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN], B[MAXN], C[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) cin >> B[i];
  for (int i = 0; i < N; ++i) cin >> C[i];

  int F[3];
  for (int i = 0; i < N; ++i) {
    F[0] = A[i]; F[1] = B[i]; F[2] = C[i];
    sort(F, F + 3);
    cout << F[1] << ' ';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
