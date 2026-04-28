#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int Q, N, L;
  cin >> Q >> N >> L;

  vector<int> A(N + 1);
  for (int i = 1; i <= N; i++) cin >> A[i];

  while (Q--) {
    int x;
    cin >> x;

    int left = 0, right = 4e6 + 1;
    while (left < right) {
      int mid = (left + right) / 2;

      int cnt = 0, l = 0;
      for (int i = 1; i <= N; i++) {
        if (A[i] - l < mid || L - A[i] < mid) continue;
        cnt++;
        l = A[i];
      }

      if (cnt >= x) left = mid + 1;
      else right = mid;
    }

    cout << left - 1 << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
