#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N, M; cin >> N >> M;
  vector<int> A(N), B(M);
  for (int& x : A) cin >> x;
  for (int& x : B) cin >> x;
  if (N > M) swap(N, M), swap(A, B);
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  int l = 0, r = INF;
  while (l < r) {
    int m = (l + r) / 2;

    int j = 0, ok = 1;
    for (int i = 0; i < N; ++i) {
      while (j < M && abs(A[i] - B[j]) > m) ++j;
      if (j == M) {
        ok = 0;
        break;
      }
      ++j;
    }
    if (ok) r = m;
    else l = m + 1;
  }

  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
