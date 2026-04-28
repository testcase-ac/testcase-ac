#include "dna.h"
#include <algorithm>

const int MAX = 1e5;
int p[3][3][MAX + 1];

void init(std::string a, std::string b) {
  int n = a.size();

  for (int w = 0; w < 3; w++) for (int x = 0; x < 3; x++) {
    for (int i = 0; i <= n; i++) p[w][x][i] = 0;
  }

  for (int i = 1; i <= n; i++) {
    for (int w = 0; w < 3; w++) for (int x = 0; x < 3; x++) {
      p[w][x][i] = p[w][x][i - 1];
    }

    int w, x;
    if (a[i - 1] == 'A') w = 0;
    if (a[i - 1] == 'T') w = 1;
    if (a[i - 1] == 'C') w = 2;
    if (b[i - 1] == 'A') x = 0;
    if (b[i - 1] == 'T') x = 1;
    if (b[i - 1] == 'C') x = 2;

    p[w][x][i]++;
  }
}

int get_distance(int x, int y) {
  int res = 0, d[3][3];
  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
    d[i][j] = p[i][j][y + 1] - p[i][j][x];
  }

  int m01 = std::min(d[0][1], d[1][0]);
  d[0][1] -= m01, d[1][0] -= m01, res += m01;

  int m02 = std::min(d[0][2], d[2][0]);
  d[0][2] -= m02, d[2][0] -= m02, res += m02;

  int m12 = std::min(d[1][2], d[2][1]);
  d[1][2] -= m12, d[2][1] -= m12, res += m12;

  int m012 = std::min({d[0][1], d[1][2], d[2][0]});
  d[0][1] -= m012, d[1][2] -= m012, d[2][0] -= m012, res += 2 * m012;

  int m021 = std::min({d[0][2], d[2][1], d[1][0]});
  d[0][2] -= m021, d[2][1] -= m021, d[1][0] -= m021, res += 2 * m021;

  for (int i = 0; i < 3; i++) for (int j = 0; j < 3; j++) {
    if (i == j || d[i][j] == 0) continue;
    return -1;
  }
  return res;
}
