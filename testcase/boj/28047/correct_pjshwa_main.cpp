#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<string, int> fi;
int fcount;
int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
}

const int MAXN = 300;
bool adj_n[MAXN + 1][MAXN + 1];
int ma[MAXN + 1], mb[MAXN + 1], N;
bool vis[MAXN + 1];

bool dfs(int a) {
  vis[a] = true;
  for (int b = 1; b <= N; ++b) {
    if (adj_n[a][b]) continue;
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    fidx(S);
  }
  assert(fcount == N);

  int R; cin >> R;
  while (R--) {
    int M, W; cin >> M >> W;
    set<int> P;
    while (M--) {
      string S; cin >> S;
      P.insert(fidx(S));
    }
    for (int i = 0; i < N; ++i) {
      if (P.count(i)) {
        // rank cannot be better than W
        for (int r = 1; r < W; ++r) {
          adj_n[i][r] = true;
        }
      } else {
        // rank cannot be W
        adj_n[i][W] = true;
      }
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; i++) {
    if (ma[i] != -1) continue;
    memset(vis, false, sizeof vis);
    if (dfs(i)) ++match;
  }
  assert(match == N);

  for (int r = 1; r <= N; ++r) {
    int p = mb[r];
    assert(p != -1);
    for (auto& [s, i] : fi) {
      if (i == p) cout << s << ' ';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
