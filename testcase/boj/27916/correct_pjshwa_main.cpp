#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3e5;
ll A[MAX + 10], P[MAX + 10], d[MAX + 10];

void solve() {
  int N, M, Q; cin >> N >> M >> Q;
  for (int i = 1; i <= N; i++) cin >> A[i];

  int left = 0, right = 1e9 + 1;
  while (left < right) {
    int mid = (left + right) / 2;

    memset(d, 0, sizeof(d));
    d[N + 1] = P[N + 1] = 1; P[N + 2] = 0;
    for (int i = N; i >= 1; i--) {
      if (i + M - 1 <= N && A[i + M - 1] <= A[i] + mid) {
        auto it = upper_bound(A, A + N + 1, A[i] + mid);
        int j = it - A;

        if (j <= N) d[i] = (P[i + M] - P[j + 1]) > 0;
        else d[i] = P[i + M] > 0;
      }
      P[i] = P[i + 1] + d[i];
    }

    if (d[1] > 0) right = mid;
    else left = mid + 1;
  }

  while (Q--) {
    int x; cin >> x;
    cout << (x >= left);
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
