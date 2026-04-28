#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int L, N, K; cin >> L >> N >> K;

  vector<int> A(N + 1);
  for (int i = 1; i <= N; i++) cin >> A[i];
  A.push_back(L); N = A.size();

  int l = 0, r = L + 1;
  for (int i = 1; i < N; i++) l = max(l, A[i] - A[i - 1]);

  while (l < r) {
    int m = (l + r) / 2;

    int acc = 0, cnt = 0;
    for (int i = 0; i < N - 1; i++) {
      if (acc + A[i + 1] - A[i] > m) {
        acc = 0;
        cnt++;
      }
      acc += A[i + 1] - A[i];
    }

    if (cnt > K) l = m + 1;
    else r = m;
  }

  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
