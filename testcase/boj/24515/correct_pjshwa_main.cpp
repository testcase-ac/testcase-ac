#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1010;
char board[MAX][MAX];
int parent[MAX * MAX], usz[MAX * MAX], from[MAX * MAX];
const ll INF = 1e18;
ll cdist[MAX * MAX];
vector<pll> graph[MAX * MAX];

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

  if (x == y) return;
  parent[y] = x;
  usz[x] += usz[y];
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    string s;
    cin >> s;
    for (int j = 1; j <= n; j++) board[i][j] = s[j - 1];
  }

  for (int i = 0; i <= n + 1; i++) for (int j = 0; j <= n + 1; j++) {
    parent[i * (n + 5) + j] = i * (n + 5) + j;
    usz[i * (n + 5) + j] = 1;
  }
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    if (board[i][j] == '.') continue;
    if (i < n && board[i][j] == board[i + 1][j]) Union(i * (n + 5) + j, (i + 1) * (n + 5) + j);
    if (j < n && board[i][j] == board[i][j + 1]) Union(i * (n + 5) + j, i * (n + 5) + j + 1);
  }
  for (int i = 3; i <= n + 1; i++) Union((i - 1) * (n + 5), i * (n + 5));
  for (int j = 1; j <= n - 1; j++) Union((n + 1) * (n + 5) + j - 1, (n + 1) * (n + 5) + j);
  for (int j = 3; j <= n + 1; j++) Union(j - 1, j);
  for (int i = 1; i <= n - 1; i++) Union((i - 1) * (n + 5) + n + 1, i * (n + 5) + n + 1);

  int s = Find(2 * (n + 5)), e = Find(2);
  usz[s] = usz[e] = 0;

  int dx[4] = {1, 1, 0, -1}, dy[4] = {0, 1, 1, 1};
  for (int i = 0; i <= n + 1; i++) for (int j = 0; j <= n + 1; j++) {
    if (i <= 1 && j <= 1) continue;
    if (i >= n && j >= n) continue;

    for (int k = 0; k < 4; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni > n + 1 || nj < 0 || nj > n + 1) continue;
      if (ni <= 1 && nj <= 1) continue;
      if (ni >= n && nj >= n) continue;

      int u = Find(i * (n + 5) + j), v = Find(ni * (n + 5) + nj);
      if (u != v) {
        graph[u].push_back({v, usz[v]});
        graph[v].push_back({u, usz[u]});
      }
    }
  }

  fill(cdist, cdist + MAX * MAX, INF);
  priority_queue<pll, vector<pll>, greater<pll>> pq;
  cdist[s] = 0;
  pq.push({0, s});

  while (!pq.empty()) {
    auto [wi, ui] = pq.top();
    pq.pop();

    if (wi > cdist[ui]) continue;

    for (auto &p : graph[ui]) {
      auto [vi, di] = p;
      if (cdist[vi] > di + wi) {
        cdist[vi] = di + wi;
        from[vi] = ui;
        pq.push({cdist[vi], vi});
      }
    }
  }

  cout << cdist[e] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
