#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};

void solve() {
  int N, K; string S; cin >> N >> K >> S;
  K = min(K, N);

  int x = 0, y = 0;
  for (int i = 0; i < N * K; ++i) {
    int dir; char c = S[i % N];
    if (c == 'U') dir = 0;
    else if (c == 'R') dir = 1;
    else if (c == 'D') dir = 2;
    else dir = 3;

    x += dx[dir]; y += dy[dir];
    if (x == 0 && y == 0) return cout << "YES\n", void();
  }
  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
