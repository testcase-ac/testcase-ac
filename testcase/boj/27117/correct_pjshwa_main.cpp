#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int OA[MAX + 1], A[MAX + 1], N;

void copy() {
  for (int i = 1; i <= N; i++) A[i] = OA[i];
}

int r() {
  int ret = 0;
  for (int i = 1; i <= N; i++) {
    while (1) {
      ret++;
      if (A[i] == i) break;

      if (A[i] > i) {
        ret++;
        break;
      }
      else {
        int v = A[i];
        A[i] = A[v];
        A[v] = v;
      }
    }
  }

  return ret;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> OA[i];

  copy();
  cout << r() << '\n';

  // int ans = 0;
  // for (int i = 1; i <= N; i++) for (int j = i + 1; j <= N; j++) {
  //   copy();
  //   swap(A[i], A[j]);
  //   ans += r();
  //   swap(A[i], A[j]);
  // }
  // cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
