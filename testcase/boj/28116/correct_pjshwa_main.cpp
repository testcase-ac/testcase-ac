#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
ll A[MAX + 1], inv[MAX + 1], ans[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    inv[A[i]] = i;
  }

  for (int i = 1; i <= N; i++) {
    int x = A[i], j = inv[i];

    int d = abs(i - j);
    ans[i] += d; ans[x] += d;

    A[i] = i; inv[i] = i;
    A[j] = x; inv[x] = j;
  }

  for (int i = 1; i <= N; i++) cout << ans[i] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
