#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tdl = tuple<double, int, int>;

const int MAX = 100;
int board[MAX][MAX];
const ll INF = 1e14;
double cdist[MAX][MAX];
double v;
int r, c;

double cost(int x, int y) {
  double s = v;
  int diff = board[0][0] - board[x][y];
  if (diff < 0) {
    for (int i = 0; i < -diff; i++) s *= 2;
  }
  else for (int i = 0; i < diff; i++) s /= 2;
  return s;
}

void dijk(int si, int sj) {
  cdist[si][sj] = 0;

  priority_queue<tdl, vector<tdl>, greater<tdl>> pq;
  pq.push({0, si, sj});

  while (!pq.empty()) {
    auto [wi, ui, uj] = pq.top();
    pq.pop();

    if (wi > cdist[ui][uj]) continue;

    double di = cost(ui, uj);

    if (ui > 0 && cdist[ui - 1][uj] > wi + di) {
      cdist[ui - 1][uj] = wi + di;
      pq.push({cdist[ui - 1][uj], ui - 1, uj});
    }
    if (uj > 0 && cdist[ui][uj - 1] > wi + di) {
      cdist[ui][uj - 1] = wi + di;
      pq.push({cdist[ui][uj - 1], ui, uj - 1});
    }
    if (ui < r - 1 && cdist[ui + 1][uj] > wi + di) {
      cdist[ui + 1][uj] = wi + di;
      pq.push({cdist[ui + 1][uj], ui + 1, uj});
    }
    if (uj < c - 1 && cdist[ui][uj + 1] > wi + di) {
      cdist[ui][uj + 1] = wi + di;
      pq.push({cdist[ui][uj + 1], ui, uj + 1});
    }
  }
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  cin >> v >> r >> c;
  v = 1 / v;
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) cin >> board[i][j], cdist[i][j] = INF;
  dijk(0, 0);
  cout << cdist[r - 1][c - 1] << '\n';
}
