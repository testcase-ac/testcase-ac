#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;
  vector<int> A(N + 1);
  for (int i = 1; i <= N; ++i) cin >> A[i];

  vector<int> D(N + 1, -1);
  D[N] = 1;
  for (int i = N - 1; i >= 1; i--) {
    if (i + A[i] > N) D[i] = 1;
    else D[i] = D[i + A[i] + 1] + 1;
  }

  for (int i = 1; i <= N; ++i) cout << D[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
