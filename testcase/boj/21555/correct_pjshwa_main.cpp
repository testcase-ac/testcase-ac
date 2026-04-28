#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int A[MAX], B[MAX]; ll d[MAX][2];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; i++) cin >> A[i];
  for (int i = 0; i < N; i++) cin >> B[i];

  d[0][0] = A[0], d[0][1] = B[0];
  for (int i = 1; i < N; i++) {
    d[i][0] = min(d[i - 1][0] + A[i], d[i - 1][1] + K + A[i]);
    d[i][1] = min(d[i - 1][0] + K + B[i], d[i - 1][1] + B[i]);
  }
  cout << min(d[N - 1][0], d[N - 1][1]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
