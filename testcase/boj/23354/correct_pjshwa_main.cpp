#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
const ll INF = 1e14;
int board[MAX][MAX], n, si, sj;
ll cdist[11][MAX][MAX];
vector<pii> ds;

void dijk(int d, int si, int sj) {
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cdist[d][i][j] = INF;
  cdist[d][si][sj] = 0;

  priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> pq;
  pq.push({0, si, sj});

  while (!pq.empty()) {
    auto [wi, ui, uj] = pq.top();
    pq.pop();

    if (wi > cdist[d][ui][uj]) continue;

    if (ui > 0 && cdist[d][ui - 1][uj] > wi + board[ui - 1][uj]) {
      cdist[d][ui - 1][uj] = wi + board[ui - 1][uj];
      pq.push({cdist[d][ui - 1][uj], ui - 1, uj});
    }
    if (uj > 0 && cdist[d][ui][uj - 1] > wi + board[ui][uj - 1]) {
      cdist[d][ui][uj - 1] = wi + board[ui][uj - 1];
      pq.push({cdist[d][ui][uj - 1], ui, uj - 1});
    }
    if (ui < n - 1 && cdist[d][ui + 1][uj] > wi + board[ui + 1][uj]) {
      cdist[d][ui + 1][uj] = wi + board[ui + 1][uj];
      pq.push({cdist[d][ui + 1][uj], ui + 1, uj});
    }
    if (uj < n - 1 && cdist[d][ui][uj + 1] > wi + board[ui][uj + 1]) {
      cdist[d][ui][uj + 1] = wi + board[ui][uj + 1];
      pq.push({cdist[d][ui][uj + 1], ui, uj + 1});
    }
  }
}

int main() {
  fast_io();

  cin >> n;

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    cin >> board[i][j];

    if (board[i][j] == 0) ds.push_back({i, j});
    if (board[i][j] == -1) board[i][j] = 0, si = i, sj = j;
  }
  int sz = ds.size();
  if (sz == 0) return cout << "0\n", 0;

  dijk(0, si, sj);
  for (int d = 1; d <= sz; d++) {
    auto [di, dj] = ds[d - 1];
    dijk(d, di, dj);
  }

  int p[sz];
  for (int i = 0; i < sz; i++) p[i] = i;

  ll mx = INF;
  do {
    ll cur = cdist[0][ds[p[0]].first][ds[p[0]].second];
    for (int i = 1; i < sz; i++) {
      cur += cdist[p[i - 1] + 1][ds[p[i]].first][ds[p[i]].second];
    }
    cur += cdist[p[sz - 1] + 1][si][sj];
    mx = min(mx, cur);
  } while (next_permutation(p, p + sz));

  cout << mx << '\n';
}
