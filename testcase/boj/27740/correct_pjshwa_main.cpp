#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3e5;
int NR[MAX + 1], A[MAX + 10];

void solve() {
  int N; cin >> N;

  int l = 0; A[0] = 1;
  fill(NR, NR + N + 1, N + 1);
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    if (A[i] == 1) NR[l] = i, l = i;
  }

  int ans = N + 1, d, lm, rm;
  for (int i = 0; i <= N; i++) {
    if (A[i] == 0) continue;

    int l = i, r = N - NR[i] + 1;
    if (ans > 2 * l + r) {
      ans = 2 * l + r;
      d = 0, lm = l;
    }
    if (ans > 2 * r + l) {
      ans = 2 * r + l;
      d = 1, rm = r;
    }
  }

  cout << ans << '\n';
  if (d) {
    for (int i = 0; i < rm; i++) cout << 'R';
    for (int i = 0; i < ans - rm; i++) cout << 'L';
  }
  else {
    for (int i = 0; i < lm; i++) cout << 'L';
    for (int i = 0; i < ans - lm; i++) cout << 'R';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
