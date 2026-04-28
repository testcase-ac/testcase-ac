#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int board[MAX][MAX];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; i++) {
    string S; cin >> S;
    for (int j = 0; j < M; j++) {
      board[i][j] = S[j] - '0';
    }
  }

  int ans = 0;
  for (int i = N - 1; i >= 0; i--) for (int j = M - 1; j >= 0; j--) {
    if (board[i][j] == 0) continue;

    ans++;
    for (int pi = 0; pi <= i; pi++) for (int pj = 0; pj <= j; pj++) {
      board[pi][pj] ^= 1;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
