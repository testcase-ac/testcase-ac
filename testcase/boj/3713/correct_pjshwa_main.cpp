#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
vector<int> graph[MAXN];
int ma[MAXN], mb[MAXN];
bool vis[MAXN];

bool dfs(int a) {
  vis[a] = true;
  for (int b : graph[a]) {
    if (mb[b] == -1 || !vis[mb[b]] && dfs(mb[b])) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) graph[i].clear();

  vector<tuple<int, string, string>> A, B;
  for (int i = 0; i < N; i++) {
    int h; string s, m, p; cin >> h >> s >> m >> p;
    if (s == "M") A.emplace_back(h, m, p);
    else B.emplace_back(h, m, p);
  }

  int Az = A.size(), Bz = B.size();
  for (int i = 0; i < Az; ++i) for (int j = 0; j < Bz; ++j) {
    auto [hi, mi, pi] = A[i]; auto [hj, mj, pj] = B[j];
    if (abs(hi - hj) <= 40 && mi == mj && pi != pj) {
      graph[i].push_back(j);
    }
  }

  int match = 0;
  fill(ma, ma + N, -1);
  fill(mb, mb + N, -1);

  for (int i = 0; i < N; i++) {
    if (ma[i] != -1) continue;
    fill(vis, vis + N, false);
    if (dfs(i)) match++;
  }

  cout << N - match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
