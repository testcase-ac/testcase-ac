#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};
int A[MAX][MAX], B[MAX][MAX];

int N, R, C, K;

void f() {
  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) B[i][j] = A[i][j];
  memset(A, -1, sizeof(A));

  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
    for (int k = 0; k < 4; k++) {
      int x = i + dx[k], y = j + dy[k];
      if (x < 0 || x >= R || y < 0 || y >= C) continue;

      if (B[x][y] == B[i][j] + 1 || (B[x][y] == 0 && B[i][j] == N - 1)) A[x][y] = B[i][j];
    }
  }
  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) {
    if (A[i][j] == -1) A[i][j] = B[i][j];
  }
}

void solve() {
  for (int i = 0; i < R; i++) for (int j = 0; j < C; j++) cin >> A[i][j];

  while (K--) f();
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) cout << A[i][j] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  while (cin >> N >> R >> C >> K) {
    if (N == 0) break;
    solve();
  }
}
