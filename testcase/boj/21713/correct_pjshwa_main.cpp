#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  vector<double> A(N);
  for (double &x : A) cin >> x;
  sort(A.begin(), A.end());
  double T; cin >> T;

  for (int s = 0; s < (1 << N); ++s) {
    int cnt = __builtin_popcount(s);
    if (cnt != N - K) continue;

    int k = 0; double sum = 0;
    for (int j = 0; j < N; ++j) {
      if (!(s & (1 << j))) continue;
      if (k > 0 && k < N - K - 1) sum += A[j];
      ++k;
    }

    double avg = sum / (N - K - 2);
    avg = round(avg * 100) / 100;
    if (avg != T) continue;

    k = 0;
    cout << fixed << setprecision(2);
    for (int j = 0; j < N; ++j) {
      if (!(s & (1 << j))) cout << A[j] << ' ';
      else {
        if (k == 0 || k == N - K - 1) cout << A[j] << ' ';
        ++k;
      }
    }
    cout << '\n';
    return;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
