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

void solve() {
  int C, D, N; cin >> C >> D >> N;
  for (int i = 0; i < N; ++i) adj[i].clear();

  vector<pair<string, string>> A(N);
  for (auto& p : A) cin >> p.first >> p.second;

  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    auto [a1, b1] = A[i]; auto [a2, b2] = A[j];
    if (a1 != b2 && a2 != b1) continue;
    if (a1[0] == 'C') adj[i].push_back(j);
    else adj[j].push_back(i);
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; i++) {
    if (ma[i] != -1) continue;

    auto a1 = A[i].first;
    if (a1[0] != 'C') continue;

    memset(vis, false, sizeof vis);
    if (dfs(i)) ++match;
  }
  cout << N - match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
