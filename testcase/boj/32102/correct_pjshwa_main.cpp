#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int dx[] = {0, 0, 1, -1}, dy[] = {1, -1, 0, 0};

void solve() {
  int N, M, Rc, Gc, Bc; cin >> N >> M >> Rc >> Gc >> Bc;
  vector<pair<int, char>> U;
  U.emplace_back(Rc, 'R');
  U.emplace_back(Gc, 'G');
  U.emplace_back(Bc, 'B');
  sort(U.begin(), U.end(), greater<>());

  queue<char> Q;
  for (int i : {0, 2, 1}) {
    auto& [cnt, c] = U[i];
    while (cnt--) Q.push(c);
  }

  int flag = N < M;
  if (flag) swap(N, M);

  vector<string> B(N, string(M, ' '));
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if ((i + j) % 2 == 1) continue;
    B[i][j] = Q.front(); Q.pop();
  }
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if ((i + j) % 2 == 0) continue;
    B[i][j] = Q.front(); Q.pop();
  }

  // check for adj same chars
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    char c = B[i][j];
    for (int k = 0; k < 4; ++k) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
      if (B[ni][nj] == c) {
        cout << "NO\n";
        return;
      }
    }
  }
  
  cout << "YES\n";
  if (flag) {
    for (int i = 0; i < M; ++i) {
      for (int j = 0; j < N; ++j) cout << B[j][i];
      cout << '\n';
    }
    return;
  }
  for (int i = 0; i < N; ++i) cout << B[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
