#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXL = 50, INF = 0x3f3f3f3f;
int N;
vector<string> A;
vector<tii> adj[MAXN][MAXL + 1];
int cdist[MAXN][MAXL + 1];

bool starts_with(const string &a, const string &b, int a_si, int b_si) {
  int az = a.size(), bz = b.size();
  if (az - a_si < bz - b_si) return false;

  for (int i = 0; i < bz - b_si; i++) {
    if (a[a_si + i] != b[b_si + i]) return false;
  }
  return true;
}

void solve() {
  A.clear();
  for (int i = 0; i < N; i++) {
    string s; cin >> s;
    A.push_back(s);

    for (int si = 0; si < MAXL; ++si) adj[i][si].clear();
  }

  for (int i = 0; i < N; ++i) {
    int iz = A[i].size();
    for (int si = 0; si < MAXL; ++si) {
      for (int j = 0; j < N; ++j) {
        if (si == 0 && i == j) continue;

        int jz = A[j].size();
        if (starts_with(A[i], A[j], si, 0)) {
          adj[i][si].emplace_back(i, si + jz, jz);
        }
        if (starts_with(A[j], A[i], 0, si)) {
          adj[i][si].emplace_back(j, iz - si, iz - si);
        }
      }
    }
  }

  memset(cdist, 0x3f, sizeof(cdist));
  priority_queue<tii, vector<tii>, greater<tii>> pq;
  for (int i = 0; i < N; ++i) pq.emplace(0, i, 0), cdist[i][0] = 0;

  while (!pq.empty()) {
    auto [dist, i, si] = pq.top(); pq.pop();
    if (cdist[i][si] < dist) continue;

    for (auto [j, sj, dj] : adj[i][si]) {
      int ndist = dist + dj;
      if (ndist < cdist[j][sj]) {
        cdist[j][sj] = ndist;
        pq.emplace(ndist, j, sj);
      }
    }
  }

  int ans = INF;
  for (int i = 0; i < N; i++) ans = min(ans, cdist[i][A[i].size()]);
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
