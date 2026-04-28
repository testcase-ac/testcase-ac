#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

char C[7][30];

//   points
// 0 +---+ 3
//   |   |
//   |   |
// 1 +---+ 4
//   |   | 
//   |   | 
// 2 +---+ 5
const int P[10][6] = {
  {1, 1, 1, 1, 1, 1}, // 0
  {0, 0, 0, 1, 1, 1}, // 1
  {1, 1, 1, 1, 1, 1}, // 2
  {1, 1, 1, 1, 1, 1}, // 3
  {1, 1, 0, 1, 1, 1}, // 4
  {1, 1, 1, 1, 1, 1}, // 5
  {1, 1, 1, 1, 1, 1}, // 6
  {1, 0, 0, 1, 1, 1}, // 7
  {1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 1, 1}, // 9
};

//   bars
//     0 
//   +---+ 
// 1 |   | 2
//   | 3 |
//   +---+
// 4 |   | 5
//   | 6 | 
//   +---+  
const int B[10][7] = {
  {1, 1, 1, 0, 1, 1, 1}, // 0
  {0, 0, 1, 0, 0, 1, 0}, // 1
  {1, 0, 1, 1, 1, 0, 1}, // 2
  {1, 0, 1, 1, 0, 1, 1}, // 3
  {0, 1, 1, 1, 0, 1, 0}, // 4
  {1, 1, 0, 1, 0, 1, 1}, // 5
  {1, 1, 0, 1, 1, 1, 1}, // 6
  {1, 0, 1, 0, 0, 1, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}, // 9
};
const int B_I[7][5] = {
  {-1, 0, 0, 0, -1},
  {1, -1, -1, -1, 2},
  {1, -1, -1, -1, 2},
  {-1, 3, 3, 3, -1},
  {4, -1, -1, -1, 5},
  {4, -1, -1, -1, 5},
  {-1, 6, 6, 6, -1},
};

void fill_points(int sj, int c) {
  for (int i = 0; i < 3; ++i) {
    C[3 * i][sj] = P[c][i] ? '+' : ' ';
    C[3 * i][sj + 4] = P[c][i + 3] ? '+' : ' ';
  }
}

void fill_bars(int sj, int c) {
  for (int i = 0; i < 7; ++i) for (int j = 0; j < 5; ++j) {
    if (B_I[i][j] == -1) continue;
    char t = B_I[i][j] % 3 == 0 ? '-' : '|';
    C[i][sj + j] = B[c][B_I[i][j]] ? t : ' ';
  }
}

void fill(int sj, int c) {
  fill_points(sj, c);
  fill_bars(sj, c);
}

string S;
void solve() {
  for (int i = 0; i < 7; i++) for (int j = 0; j < 29; j++) C[i][j] = ' ';
  C[2][14] = C[4][14] = 'o';
  fill(0, S[0] - '0'); fill(7, S[1] - '0');
  fill(17, S[3] - '0'); fill(24, S[4] - '0');

  for (int i = 0; i < 7; ++i) cout << C[i] << '\n';
}

int main() {
  fast_io();

  while (cin >> S) {
    if (S == "end") {
      cout << "end\n";
      break;
    }
    solve();
    cout << "\n\n";
  }
}
