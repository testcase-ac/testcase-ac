#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int dx[3] = {0, 1, -1}, dy[3] = {-1, 0, 0};

int N, M;
void solve_W0() {
  vector<string> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  int parent[N * M], usz[N * M];
  function<int(int)> Find = [&](int x) {
    return parent[x] == x ? x : parent[x] = Find(parent[x]);
  };
  function<void(int, int)> Union = [&](int x, int y) {
    x = Find(x), y = Find(y);
    if (x == y) return;
    if (usz[x] < usz[y]) swap(x, y);
    parent[y] = x;
    usz[x] += usz[y];
  };

  iota(parent, parent + N * M, 0);
  fill(usz, usz + N * M, 1);

  int ans = 0;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (A[i][j] == '0') continue;

    for (int k = 0; k < 3; k++) {
      int ni = i + dx[k], nj = j + dy[k];
      if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

      if (A[ni][nj] == '0') continue;
      Union(i * M + j, ni * M + nj);
    }
    ans = max(ans, usz[Find(i * M + j)]);
  }

  cout << ans << '\n';
}

void solve() {
  int W; cin >> N >> M >> W;
  if (W == 0) return solve_W0();

  vector<string> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  int parent[N * M], usz[N * M];
  function<int(int)> Find = [&](int x) {
    return parent[x] == x ? x : parent[x] = Find(parent[x]);
  };
  function<void(int, int)> Union = [&](int x, int y) {
    x = Find(x), y = Find(y);
    if (x == y) return;
    if (usz[x] < usz[y]) swap(x, y);
    parent[y] = x;
    usz[x] += usz[y];
  };

  int ll = 0, rr = N * M + 1;
  while (ll < rr) {
    int mcnt = (ll + rr) / 2;

    iota(parent, parent + N * M, 0);
    fill(usz, usz + N * M, 1);

    int wcnt = 0, msz = 0, f = 1;
    for (int j = 0; j < M; j++) {
      if (wcnt > W) break;

      for (int i = 0; i < N; i++) {
        if (A[i][j] == '1') {
          for (int k = 0; k < 3; k++) {
            int ni = i + dx[k], nj = j + dy[k];
            if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;

            if (A[ni][nj] == '0') continue;
            Union(i * M + j, ni * M + nj);
          }
        }
        msz = max(msz, usz[Find(i * M + j)]);
      }

      if (msz > mcnt) {
        msz = 0; wcnt++;
        for (int i = 0; i < N; i++) parent[i * M + j] = i * M + j, usz[i * M + j] = 1;
        for (int i = 0; i < N; i++) {
          for (int k = 1; k < 3; k++) {
            int ni = i + dx[k], nj = j + dy[k];
            if (ni < 0 || ni >= N || nj < 0 || nj >= M) continue;
            if (A[i][j] == '1' && A[ni][nj] == '1') Union(i * M + j, ni * M + nj);
          }
          msz = max(msz, usz[Find(i * M + j)]);
        }
      }

      if (msz > mcnt) {
        f = 0; break;
      }
    }

    f &= wcnt <= W;
    if (f) rr = mcnt;
    else ll = mcnt + 1;
  }

  cout << ll << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
