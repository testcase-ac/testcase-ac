#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 60, INF = 0x3f3f3f3f;
const int dx1[3] = {0, 0, 1}, dx2[3] = {0, 0, -1}, dy[3] = {1, -1, 0};
bool vis[MAX][MAX];
vector<int> ans{0, 1, 1, 1};
vector<pii> cur;
set<vector<pii>> S;
int it;

void dfs(int i) {
  vector<pii> ind = cur;
  if (i == it) {
    sort(ind.begin(), ind.end());
    auto [minx, miny] = ind[0];
    int pty = (minx + miny) % 2;

    for (auto& [x, y] : ind) x -= minx, y -= miny;
    ind.push_back({pty, INF});

    S.insert(ind);
    return;
  }

  for (auto& [x, y] : ind) {
    for (int d = 0; d < 3; d++) {
      int nx, ny;
      if ((x + y) % 2 == 0) nx = x + dx1[d], ny = y + dy[d];
      else nx = x + dx2[d], ny = y + dy[d];

      if (vis[nx][ny]) continue;

      vis[nx][ny] = true;
      cur.push_back({nx, ny});
      dfs(i + 1);
      cur.pop_back();
      vis[nx][ny] = false;
    }
  }
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; cin >> N;
  cout << N << '\n';
}

int main() {
  fast_io();

  for (it = 4; it <= 16; it++) {
    cur.push_back({30, 30});
    vis[30][30] = true;

    cout << "it: " << it << endl;

    dfs(1);

    cur.pop_back();
    vis[30][30] = false;
    ans.push_back(S.size());

    // for (auto& v : S) {
    //   for (auto& [x, y] : v) cout << "(" << x << ", " << y << ") ";
    //   cout << endl;
    // }
    cout << "S.size(): " << S.size() << endl;

    S.clear();
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
