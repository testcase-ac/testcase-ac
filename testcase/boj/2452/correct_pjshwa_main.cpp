#include <bits/stdc++.h>
#define pii pair<int, int>
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4, INF = 2e9;
vector<int> graph[MAX + 1];
int board[100][100];
int parent[MAX + 1], dist[MAX + 1];
int tmv = 100;

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void add_edge(int x, int y) {
  graph[x].push_back(y);
}

int bfs(int sv) {
  int r = 0;
  queue<int> q;
  fill(dist, dist + MAX + 1, INF);
  dist[sv] = 0;
  q.push(sv);

  while (!q.empty()) {
    int cv = q.front();
    q.pop();
    for (int nv : graph[cv]) {
      if (dist[nv] != INF) continue;
      dist[nv] = dist[cv] + 1;
      q.push(nv);
      r = dist[nv];
      if (r >= tmv) return r;
    }
  }
  return r;
}

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> board[i][j];
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) parent[i * m + j] = i * m + j;

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    int c = board[i][j];
    int x = i * m + j;
    if (i > 0 && c == board[i - 1][j]) Union(x, (i - 1) * m + j);
    if (j > 0 && c == board[i][j - 1]) Union(x, i * m + j - 1);
    if (i < n - 1 && c == board[i + 1][j]) Union(x, (i + 1) * m + j);
    if (j < m - 1 && c == board[i][j + 1]) Union(x, i * m + j + 1);
  }

  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    int x = Find(i * m + j);
    if (i > 0 && x != Find((i - 1) * m + j)) add_edge(x, Find((i - 1) * m + j));
    if (j > 0 && x != Find(i * m + j - 1)) add_edge(x, Find(i * m + j - 1));
    if (i < n - 1 && x != Find((i + 1) * m + j)) add_edge(x, Find((i + 1) * m + j));
    if (j < m - 1 && x != Find(i * m + j + 1)) add_edge(x, Find(i * m + j + 1));
  }

  set<int> c;
  for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
    bool ibound = 5 * i < n || 5 * i > 4 * n, jbound = 5 * j < m || 5 * j > 4 * m;
    if (ibound && jbound) continue;

    int x = Find(i * m + j);
    if (!c.count(x)) {
      c.insert(x);
      tmv = min(tmv, bfs(x));
    }
  }
  cout << tmv;
}
