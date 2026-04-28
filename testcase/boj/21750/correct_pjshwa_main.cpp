#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;
const int dx[8] = {1, 1, 2, 2, -1, -1, -2, -2};
const int dy[8] = {2, -2, 1, -1, 2, -2, 1, -1};
int cdist[8][8][8][8];

void solve() {
  string Ws, Bs, We, Be; cin >> Ws >> Bs >> We >> Be;
  int Wsi = Ws[0] - 'a', Wsj = Ws[1] - '1', Bsi = Bs[0] - 'a', Bsj = Bs[1] - '1';
  int Wei = We[0] - 'a', Wej = We[1] - '1', Bei = Be[0] - 'a', Bej = Be[1] - '1';

  memset(cdist, 0x3f, sizeof(cdist));
  queue<tuple<int, int, int, int>> q;
  q.emplace(Wsi, Wsj, Bsi, Bsj); cdist[Wsi][Wsj][Bsi][Bsj] = 0;
  while (!q.empty()) {
    auto [wi, wj, bi, bj] = q.front(); q.pop();
    for (int k = 0; k < 8; ++k) {
      int nwi = wi + dx[k], nwj = wj + dy[k];
      if (nwi < 0 || nwi >= 8 || nwj < 0 || nwj >= 8) continue;
      if (nwi == bi && nwj == bj) continue;
      if (cdist[nwi][nwj][bi][bj] == INF) {
        cdist[nwi][nwj][bi][bj] = cdist[wi][wj][bi][bj] + 1;
        q.emplace(nwi, nwj, bi, bj);
      }
    }
    for (int k = 0; k < 8; ++k) {
      int nbi = bi + dx[k], nbj = bj + dy[k];
      if (nbi < 0 || nbi >= 8 || nbj < 0 || nbj >= 8) continue;
      if (nbi == wi && nbj == wj) continue;
      if (cdist[wi][wj][nbi][nbj] == INF) {
        cdist[wi][wj][nbi][nbj] = cdist[wi][wj][bi][bj] + 1;
        q.emplace(wi, wj, nbi, nbj);
      }
    }
  }

  if (cdist[Wei][Wej][Bei][Bej] == INF) {
    cout << "-1\n";
    return;
  }
  cout << cdist[Wei][Wej][Bei][Bej] << '\n';

  q.emplace(Wei, Wej, Bei, Bej);
  vector<string> path;
  while (!q.empty()) {
    auto [wi, wj, bi, bj] = q.front(); q.pop();

    int ok = 0;
    for (int k = 0; k < 8 && !ok; ++k) {
      int pwi = wi + dx[k], pwj = wj + dy[k];
      if (pwi < 0 || pwi >= 8 || pwj < 0 || pwj >= 8) continue;
      if (pwi == bi && pwj == bj) continue;
      if (cdist[pwi][pwj][bi][bj] == cdist[wi][wj][bi][bj] - 1) {
        path.emplace_back("W " + string(1, char(wi + 'a')) + to_string(wj + 1));
        q.emplace(pwi, pwj, bi, bj);
        ok = 1;
      }
    }
    for (int k = 0; k < 8 && !ok; ++k) {
      int pbi = bi + dx[k], pbj = bj + dy[k];
      if (pbi < 0 || pbi >= 8 || pbj < 0 || pbj >= 8) continue;
      if (pbi == wi && pbj == wj) continue;
      if (cdist[wi][wj][pbi][pbj] == cdist[wi][wj][bi][bj] - 1) {
        path.emplace_back("B " + string(1, char(bi + 'a')) + to_string(bj + 1));
        q.emplace(wi, wj, pbi, pbj);
        ok = 1;
      }
    }
  }

  for (auto it = path.rbegin(); it != path.rend(); ++it) cout << *it << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
