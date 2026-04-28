#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char board[30][30];
int parent[900];

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

vector<int> graph[900];
bool vis[900];

void add_edge(int x, int y) {
  graph[x].push_back(y);
  // graph[y].push_back(x);
}

int bfs(int sv) {
  // Vertex, depth
  queue<pii> q;
  q.push({sv, 0});

  int vtx, dpt, mv = 0;
  while (!q.empty()) {
    tie(vtx, dpt) = q.front();
    q.pop();

    if (vis[vtx]) continue;
    vis[vtx] = true;
    mv = max(mv, dpt);

    for (auto dst : graph[vtx]) {
      if (!vis[dst]) q.push({dst, dpt + 1});
    }
  }

  return mv;
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> board[i];
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) parent[i * n + j] = i * n + j;

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    char c = board[i][j];
    int x = i * n + j;
    if (i > 0 && c == board[i - 1][j]) Union(x, (i - 1) * n + j);
    if (j > 0 && c == board[i][j - 1]) Union(x, i * n + j - 1);
    if (i < n - 1 && c == board[i + 1][j]) Union(x, (i + 1) * n + j);
    if (j < n - 1 && c == board[i][j + 1]) Union(x, i * n + j + 1);
  }

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    int x = Find(i * n + j);
    if (i > 0 && x != Find((i - 1) * n + j)) add_edge(x, Find((i - 1) * n + j));
    if (j > 0 && x != Find(i * n + j - 1)) add_edge(x, Find(i * n + j - 1));
    if (i < n - 1 && x != Find((i + 1) * n + j)) add_edge(x, Find((i + 1) * n + j));
    if (j < n - 1 && x != Find(i * n + j + 1)) add_edge(x, Find(i * n + j + 1));
  }

  int mv = 2e9;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    memset(vis, 0, sizeof(vis));
    mv = min(mv, bfs(Find(i * n + j)));
  }
  cout << mv;

}
