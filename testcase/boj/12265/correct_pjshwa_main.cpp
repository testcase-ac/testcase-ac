#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int tc; double A[MAXN], B[MAXN];

void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) cin >> B[i];
  sort(A, A + N); sort(B, B + N);

  int cnt1 = 0, cnt2 = 0, j = 0;
  for (int i = 0; i < N; ++i) {
    while (j < N && B[j] <= A[i]) ++j;
    if (j < N) ++cnt1, ++j;
  }
  int i = 0;
  for (int j = 0; j < N; ++j) {
    while (i < N && A[i] <= B[j]) ++i;
    if (i < N) ++cnt2, ++i;
  }
  cout << cnt2 << ' ' << N - cnt1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
