#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  int U, D; cin >> U >> D;
  vector<int> ans(N, -1);

  for (int i = 0; i < N; i++) {
    if (A[i] == 1 && U) U--, ans[i] = 1;
  }
  for (int i = 0; i < N; i++) {
    if (A[i] == 2 && D) D--, ans[i] = 0;
  }
  for (int i = 0; i < N; i++) {
    if (A[i] == 3) {
      if (U) U--, ans[i] = 1;
      else if (D) D--, ans[i] = 0;
    }
  }

  for (int i = 0; i < N; i++) {
    if (ans[i] == -1) return cout << "NO\n", void();
  }

  cout << "YES\n";
  for (int i = 0; i < N; i++) {
    cout << (ans[i] ? "U" : "D");
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
