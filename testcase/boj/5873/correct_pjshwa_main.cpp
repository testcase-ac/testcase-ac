#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 30;
const ll INF = 1e14;
char board[MAX + 1][MAX + 1];
int n, a, b, si, sj;
ll cdist[MAX][MAX], mdist;

int dist(int ai, int aj, int bi, int bj) {
  if (board[ai][aj] == board[bi][bj]) return a;
  else return b;
}

void dijk(int si, int sj) {
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cdist[i][j] = INF;
  cdist[si][sj] = 0;

  priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> pq;
  pq.push({0, si, sj});

  while (!pq.empty()) {
    auto [wi, ui, uj] = pq.top();
    pq.pop();

    if (wi > cdist[ui][uj]) continue;
    mdist = max(mdist, wi);

    if (ui > 0 && cdist[ui - 1][uj] > wi + dist(ui - 1, uj, ui, uj)) {
      cdist[ui - 1][uj] = wi + dist(ui - 1, uj, ui, uj);
      pq.push({cdist[ui - 1][uj], ui - 1, uj});
    }
    if (ui < n - 1 && cdist[ui + 1][uj] > wi + dist(ui + 1, uj, ui, uj)) {
      cdist[ui + 1][uj] = wi + dist(ui + 1, uj, ui, uj);
      pq.push({cdist[ui + 1][uj], ui + 1, uj});
    }
    if (uj > 0 && cdist[ui][uj - 1] > wi + dist(ui, uj - 1, ui, uj)) {
      cdist[ui][uj - 1] = wi + dist(ui, uj - 1, ui, uj);
      pq.push({cdist[ui][uj - 1], ui, uj - 1});
    }
    if (uj < n - 1 && cdist[ui][uj + 1] > wi + dist(ui, uj + 1, ui, uj)) {
      cdist[ui][uj + 1] = wi + dist(ui, uj + 1, ui, uj);
      pq.push({cdist[ui][uj + 1], ui, uj + 1});
    }
  }
}

int main() {
  fast_io();

  cin >> n >> a >> b;
  for (int i = 0; i < n; i++) cin >> board[i];

  ll ans = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    mdist = 0;
    dijk(i, j);
    ans = max(ans, mdist);
  }
  cout << ans << '\n';
}
