#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int P[MAX + 5], O[MAX + 5];

void solve() {
  int N, M, K, X;
  cin >> N >> M >> K >> X;

  P[0] = X;
  for (int i = 1; i <= N; i++) {
    cin >> P[i];
    P[i] += P[i - 1];
    if (P[i] < K) O[i] = 1;
    O[i] += O[i - 1];
  }

  while (M--) {
    int l, r;
    cin >> l >> r;
    cout << O[r - 1] - O[l - 1] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
