#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 10000;
vector<int> adj[MAXN];
int ma[MAXN], mb[MAXN];
bool vis[MAXN];

bool dfs(int a) {
  vis[a] = true;
  for (int b : adj[a]) {
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

bool is_adj(int x1, int y1, int x2, int y2) {
  return abs(x1 - x2) + abs(y1 - y2) == 1;
}

void solve() {
  int N; cin >> N;

  vector<tuple<int, int, int, int>> points(N);
  for (int i = 0; i < N; ++i) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    points[i] = {x1, y1, x2, y2};
  }

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (i == j) continue;
    auto [x1, y1, x2, y2] = points[i];
    auto [x3, y3, x4, y4] = points[j];

    if (is_adj(x1, y1, x3, y3)) {
      adj[i].push_back(j);
      adj[j].push_back(i);
    }
    if (is_adj(x1, y1, x4, y4)) {
      adj[i].push_back(j + N);
      adj[j + N].push_back(i);
    }
    if (is_adj(x2, y2, x3, y3)) {
      adj[i + N].push_back(j);
      adj[j].push_back(i + N);
    }
    if (is_adj(x2, y2, x4, y4)) {
      adj[i + N].push_back(j + N);
      adj[j + N].push_back(i + N);
    }
  }

  fill(ma, ma + 2 * N, -1);
  fill(mb, mb + 2 * N, -1);

  int match = 0;
  for (int i = 0; i < 2 * N; ++i) {
    auto [x1, y1, x2, y2] = points[i % N];
    int x = (i < N) ? x1 : x2;
    int y = (i < N) ? y1 : y2;
    if ((x + y) % 2 != 0 || ma[i] != -1) continue;
    fill(vis, vis + 2 * N, false);
    if (dfs(i)) ++match;
  }
  if (match < N) return cout << "impossible\n", void();

  map<pii, int> marks; int idx = 0;
  for (int i = 0; i < 2 * N; ++i) {
    auto [x1, y1, x2, y2] = points[i % N];
    int x = (i < N) ? x1 : x2;
    int y = (i < N) ? y1 : y2;
    if ((x + y) % 2 != 0) continue;

    auto [x3, y3, x4, y4] = points[ma[i] % N];
    int xd = (ma[i] < N) ? x3 : x4;
    int yd = (ma[i] < N) ? y3 : y4;

    marks[{x, y}] = marks[{xd, yd}] = idx++;
  }

  for (auto& [x1, y1, x2, y2] : points) {
    int mark1 = marks[{x1, y1}];
    int mark2 = marks[{x2, y2}];
    cout << mark1 << ' ' << mark2 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
