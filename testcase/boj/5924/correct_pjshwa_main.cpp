#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 250;
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

void solve() {
  int N; cin >> N;

  vector<tuple<int, int, int>> A, B;
  for (int i = 0; i < N; ++i) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    if (x1 == x2) A.emplace_back(x1, min(y1, y2), max(y1, y2));
    else B.emplace_back(y1, min(x1, x2), max(x1, x2));
  }
  N = A.size(); int M = B.size();

  // if intersection, add edge
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    auto [ax, ay1, ay2] = A[i]; auto [by, bx1, bx2] = B[j];
    if (ax >= bx1 && ax <= bx2 && by >= ay1 && by <= ay2) {
      adj[i].push_back(j);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; ++i) {
    if (ma[i] != -1) continue;
    fill(vis, vis + N, false);
    if (dfs(i)) ++match;
  }
  cout << N + M - match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
