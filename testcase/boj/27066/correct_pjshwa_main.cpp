#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N);

  double avg = 0;
  for (int i = 0; i < N; i++) avg += A[i];
  avg /= N;

  if (N == 1) cout << A[0] << '\n';
  if (N == 2) cout << fixed << setprecision(10) << avg << '\n';
  if (N >= 3) {
    double ans = A[N - 2];
    ans = max(ans, avg);
    cout << fixed << setprecision(10) << ans << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
