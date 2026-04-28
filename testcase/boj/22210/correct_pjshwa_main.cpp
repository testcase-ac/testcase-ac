#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 600, MAXB = 4;
char board[MAX + 1][MAX + 1], result[MAX + 1][MAX + 1];
bool d[MAX + 1][1 << MAXB][1 << MAXB];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  for (int b = 0; b < (1 << MAXB); b++) d[0][0][b] = true;
  for (int j = 1; j <= M; j++) {
    for (int pb2 = 0; pb2 < (1 << MAXB); pb2++) for (int pb1 = 0; pb1 < (1 << MAXB); pb1++) {
      if (!d[j - 1][pb2][pb1]) continue;

      for (int nb = 0; nb < (1 << MAXB); nb++) {
        int t[N]{};

        for (int i = 0; i < N; i++) {
          if (pb2 & (1 << i)) t[i]++;
          if (pb1 & (1 << i)) t[i]++;
          if (nb & (1 << i)) t[i]++;

          if (i > 0 && (pb2 & (1 << (i - 1)))) t[i]++;
          if (i > 0 && (pb1 & (1 << (i - 1)))) t[i]++;
          if (i > 0 && (nb & (1 << (i - 1)))) t[i]++;

          if (i < N - 1 && (pb2 & (1 << (i + 1)))) t[i]++;
          if (i < N - 1 && (pb1 & (1 << (i + 1)))) t[i]++;
          if (i < N - 1 && (nb & (1 << (i + 1)))) t[i]++;
        }

        bool ok = true;
        for (int i = 0; i < N; i++) {
          int v = board[i][j - 1] - '0';
          if (t[i] != v) {
            ok = false;
            break;
          }
        }

        if (ok) d[j][pb1][nb] = true;
      }
    }
  }

  bool ok = false;
  int b1, b2 = 0;
  for (int b = 0; b < (1 << MAXB); b++) {
    if (d[M][b][0]) {
      ok = true;
      b1 = b;
      break;
    }
  }
  assert(ok);

  // backtrack answer
  for (int j = M; j >= 1; j--) {
    for (int b = 0; b < (1 << MAXB); b++) {
      if (!d[j - 1][b][b1]) continue;

      int t[N]{};
      for (int i = 0; i < N; i++) {
        if (b & (1 << i)) t[i]++;
        if (b1 & (1 << i)) t[i]++;
        if (b2 & (1 << i)) t[i]++;

        if (i > 0 && (b & (1 << (i - 1)))) t[i]++;
        if (i > 0 && (b1 & (1 << (i - 1)))) t[i]++;
        if (i > 0 && (b2 & (1 << (i - 1)))) t[i]++;

        if (i < N - 1 && (b & (1 << (i + 1)))) t[i]++;
        if (i < N - 1 && (b1 & (1 << (i + 1)))) t[i]++;
        if (i < N - 1 && (b2 & (1 << (i + 1)))) t[i]++;
      }

      bool ok = true;
      for (int i = 0; i < N; i++) {
        int v = board[i][j - 1] - '0';
        if (t[i] != v) {
          ok = false;
          break;
        }
      }

      if (!ok) continue;

      for (int i = 0; i < N; i++) {
        if (b1 & (1 << i)) result[i][j - 1] = 'X';
        else result[i][j - 1] = '.';
      }

      b2 = b1;
      b1 = b;
      break;
    }
  }

  for (int i = 0; i < N; i++) cout << result[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
