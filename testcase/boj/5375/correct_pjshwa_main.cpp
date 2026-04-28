#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int dx[6] = {1, 0, -1, -1, 0, 1};
const int dy_e[6] = {0, 1, 0, -1, -1, -1};
const int dy_o[6] = {1, 1, 1, 0, -1, 0};
const int MAX = 5000, BIAS = 2500;
int b[MAX][MAX], o[10001];

void solve() {
  int n;
  cin >> n;
  cout << o[n] << '\n';
}

int main() {
  fast_io();

  vector<tuple<int, int, int>> initial = {
    {0, 0, 1},
    {1, 0, 2},
    {0, 1, 3},
    {-1, 0, 4},
    {-1, -1, 5},
    {0, -1, 2}
  };

  int i = 0;
  for (auto& [x, y, t] : initial) {
    b[x + BIAS][y + BIAS] = t;
    o[++i] = t;
  }

  int u[6] = {0, 1, 2, 1, 1, 1};
  int x = 0, y = -1, k = 0;
  for (int i = 7; i <= 1e4; i++) {
    int nk = (k + 1) % 6, nx, ny;
    if (x & 1) nx = x + dx[nk], ny = y + dy_o[nk];
    else nx = x + dx[nk], ny = y + dy_e[nk];

    if (b[nx + BIAS][ny + BIAS] == 0) {
      x = nx, y = ny, k = nk;
    }
    else {
      if (x & 1) x = x + dx[k], y = y + dy_o[k];
      else x = x + dx[k], y = y + dy_e[k];
    }

    int p[6] = {0};
    for (int k = 0; k < 6; k++) {
      if (x & 1) nx = x + dx[k], ny = y + dy_o[k];
      else nx = x + dx[k], ny = y + dy_e[k];

      if (b[nx + BIAS][ny + BIAS]) p[b[nx + BIAS][ny + BIAS]] = 1;
    }

    vector<int> candidates;
    for (int c = 1; c <= 5; c++) if (p[c] == 0) candidates.push_back(c);

    sort(candidates.begin(), candidates.end(), [&] (int a, int b) {
      if (u[a] == u[b]) return a < b;
      return u[a] < u[b];
    });

    int c = candidates[0];
    u[c]++;
    b[x + BIAS][y + BIAS] = c;
    o[i] = c;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
