#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int A[MAX + 1];

void solve() {
  int N, K;
  cin >> N >> K;
  for (int i = 1; i <= N; i++) cin >> A[i];
  if (K <= 3) return cout << (N - 1) / 3 + 1 << '\n', void();

  int streak = 1, last = A[1];
  for (int i = 2; i <= N; i++) {
    if (abs(A[i] - last) == 1) {
      streak++;
      last = A[i];
    }
    else {
      streak = 1;
      last = A[i];
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
