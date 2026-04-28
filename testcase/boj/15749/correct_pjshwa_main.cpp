#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 250;
int f[MAX];
bool d[MAX][MAX];
pii boots[MAX];

int main() {
  fast_io();

  int n, b;
  cin >> n >> b;
  for (int i = 0; i < n; i++) cin >> f[i];
  for (int i = 0; i < b; i++) cin >> boots[i].first >> boots[i].second;

  for (int j = 0; j < b; j++) d[0][j] = true;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < b; j++) {
      auto [si, di] = boots[j];
      if (f[i] > si) continue;
      for (int k = 1; k <= di; k++) {
        if (i - k >= 0 && d[i - k][j]) d[i][j] = true;
      }
      for (int k = 0; k < j; k++) if (d[i][k]) d[i][j] = true;
    }
  }

  for (int j = 0; j < b; j++) {
    if (d[n - 1][j]) return cout << j << '\n', 0;
  }
}
