#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
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

int N, M, S, V;
void solve() {
  int D = S * V;

  vector<pair<double, double>> A(N), B(M);
  for (auto& [x, y] : A) cin >> x >> y;
  for (auto& [x, y] : B) cin >> x >> y;

  for (int i = 0; i < N; ++i) {
    adj[i].clear();
    for (int j = 0; j < M; ++j) {
      auto [ax, ay] = A[i]; auto [bx, by] = B[j];
      auto dist = sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
      if (dist <= D) adj[i].push_back(j);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; i++) {
    if (ma[i] != -1) continue;
    memset(vis, 0, sizeof vis);
    if (dfs(i)) ++match;
  }
  cout << N - match << '\n';
}

int main() {
  fast_io();

  while (cin >> N >> M >> S >> V) solve();
}
