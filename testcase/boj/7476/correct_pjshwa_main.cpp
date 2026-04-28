#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500, INF = 0x3f3f3f3f;
int A[MAXN], B[MAXN], S[MAXN], d[MAXN][MAXN];
pii from[MAXN][MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  int M; cin >> M;
  for (int i = 0; i < M; i++) cin >> B[i];

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    from[i][j] = {-1, -1};
  }

  memset(S, -1, sizeof(S)); int ans = 0, ei, ej;
  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (A[i] != B[j]) continue;
    S[j] = i; d[i][j] = 1;
    for (int pj = 0; pj < j; pj++) {
      if (B[pj] >= B[j] || S[pj] == -1) continue;
      int pi = S[pj];
      if (pj != -1 && d[pi][pj] + 1 > d[i][j]) {
        d[i][j] = d[pi][pj] + 1;
        from[i][j] = {pi, pj};
      }
    }
    if (ans < d[i][j]) {
      ans = d[i][j];
      ei = i; ej = j;
    }
  }

  cout << ans << '\n';
  if (ans == 0) return;
  
  vector<int> traj;
  while (from[ei][ej].first != -1) {
    traj.push_back(A[ei]);
    tie(ei, ej) = from[ei][ej];
  }
  traj.push_back(A[ei]);
  assert((int)traj.size() == ans);

  reverse(traj.begin(), traj.end());
  for (int x : traj) cout << x << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
