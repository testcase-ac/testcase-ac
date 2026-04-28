#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
vector<int> adj[MAXN];
int Ax[MAXN], Ay[MAXN], Bx[MAXN], By[MAXN];
int ma[MAXN], mb[MAXN];
int N;
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

void init() {
  for (int i = 0; i < N; ++i) {
    adj[i].clear();
    ma[i] = mb[i] = -1;
  }
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> Ax[i] >> Ay[i];
  for (int i = 0; i < N; ++i) cin >> Bx[i] >> By[i];

  int l = 0, r = 4e8 + 1;
  while (l < r) {
    int m = (l + r) / 2;

    init();
    for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
      if (abs(Ax[i] - Bx[j]) + abs(Ay[i] - By[j]) <= m) {
        adj[i].push_back(j);
      }
    }

    int match = 0;
    for (int i = 0; i < N; ++i) {
      fill(vis, vis + N, false);
      if (dfs(i)) ++match;
    }
    if (match == N) r = m;
    else l = m + 1;
  }

  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
