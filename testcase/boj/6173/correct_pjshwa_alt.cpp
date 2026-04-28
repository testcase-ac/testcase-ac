#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int C[MAXN];

void solve() {
  int N, K, j = 0; cin >> N >> K;
  for (int i = 1; i <= K; ++i) {
    int x; cin >> x;
    while (x--) C[j++] = i;
  }
  for (int i = 0; i < N / 2; ++i) {
    cout << C[i] << ' ' << C[i + N / 2] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
