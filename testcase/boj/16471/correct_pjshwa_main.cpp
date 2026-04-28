#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX], B[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < N; i++) cin >> B[i];
  sort(A, A + N);
  sort(B, B + N);

  int cnt = 0, p = 0;
  for (int i = 0; i < N; i++) {
    while (p < N && B[p] <= A[i]) p++;

    if (p == N) break;
    cnt++; p++;
  }

  if (2 * cnt >= N + 1) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
