#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool issq(long double x) {
  long long sr = sqrt(x);
  return (sr * sr == x);
}

char board[10][10];
int main() {
  fast_io();

  int h, w;
  cin >> h >> w;

  for (int i = 0; i < h; i++) cin >> board[i];

  int mv = -1;
  string s;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {

      for (int dh = -10; dh < 10; dh++) {

        for (int dw = -10; dw < 10; dw++) {
          if (dh == 0 && dw == 0) continue;

          for (int steps = 1; steps < 10; steps++) {
            s = "";

            for (int step = 0; step < steps; step++) {
              if (
                i + step * dh >= h ||
                j + step * dw >= w ||
                i + step * dh < 0 ||
                j + step * dw < 0
              ) break;

              s += board[i + step * dh][j + step * dw];
            }
          
            if (s.size()) {
              int res = stoi(s);
              if (issq(res)) mv = max(res, mv);
            }
          }
        }
      }
    }
  }

  cout << mv << '\n';
}
