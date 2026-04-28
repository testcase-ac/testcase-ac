#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5, INF = 0x3f3f3f3f;
int cdist[MAX + 1][2];
bool bvis[MAX + 1][2];

void solve() {
  int N, A, B, DA, DB;
  cin >> N >> A >> B >> DA >> DB;

  for (int i = 1; i <= N; i++) {
    cdist[i][0] = cdist[i][1] = INF;
  }
  queue<tii> q;
  q.push({A, 0, 0});
  cdist[A][0] = 0;

  while (!q.empty()) {
    auto [v, p, c] = q.front(); q.pop();

    int x1 = v + DA, x2 = v - DA;
    if (x1 > N) x1 -= N;
    if (x2 < 1) x2 += N;
    if (cdist[x1][p ^ 1] > c + 1) {
      cdist[x1][p ^ 1] = c + 1;
      q.push({x1, p ^ 1, c + 1});
    }
    if (cdist[x2][p ^ 1] > c + 1) {
      cdist[x2][p ^ 1] = c + 1;
      q.push({x2, p ^ 1, c + 1});
    }
  }

  q.push({B, 0, 0});
  bvis[B][0] = true;

  int ans = INF;
  while (!q.empty()) {
    auto [v, p, c] = q.front(); q.pop();

    if (cdist[v][p] != INF) {
      int mdist = max(cdist[v][p], c);
      ans = min(ans, mdist * 2);
    }
    if (cdist[v][p ^ 1] != INF) {
      int mdist;
      if (cdist[v][p ^ 1] > c) mdist = cdist[v][p ^ 1];
      else mdist = c + 1;
      ans = min(ans, mdist * 2 - 1);
    }

    int x1 = v + DB, x2 = v - DB;
    if (x1 > N) x1 -= N;
    if (x2 < 1) x2 += N;
    if (!bvis[x1][p ^ 1]) {
      bvis[x1][p ^ 1] = true;
      q.push({x1, p ^ 1, c + 1});
    }
    if (!bvis[x2][p ^ 1]) {
      bvis[x2][p ^ 1] = true;
      q.push({x2, p ^ 1, c + 1});
    }
  }

  if (ans == INF) cout << "Evil Galazy\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
