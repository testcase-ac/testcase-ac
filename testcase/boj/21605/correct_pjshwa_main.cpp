#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N - 1; i++) cout << "1 -1 ";
  cout << "-1 1\n";

  // int ans = 0;
  // for (int s = 0; s < (1 << N); s++) {
  //   int A[N], dt = 0;
  //   for (int i = 0; i < N; i++) {
  //     if (s & (1 << i)) A[i] = 1;
  //     else A[i] = -1;
  //     dt += A[i];
  //   }
  //   if (dt != 0) continue;

  //   int B[N / 2]{};
  //   for (int i = 0; i < N / 2; i++) {
  //     B[i] = (i ? B[i - 1] : 0) * A[2 * i] + A[2 * i + 1];
  //   }

  //   int score = B[N / 2 - 1];
  //   if (score != N / 2) continue;

  //   cout << "seq: ";
  //   for (int i = 0; i < N; i++) cout << A[i] << ' ';
  //   cout << ", score: " << B[N / 2 - 1] << '\n';
  // }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
