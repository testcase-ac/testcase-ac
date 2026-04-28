#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;
int LL[10], LR[10], AL[10], PE[10];
int N, C;
bool vis[10];
vector<int> cur;
int ans = 0;

void dfs(int i) {
  if (i == C) {
    int val = LR[cur[0]] + LL[cur.back()];
    for (int j = 1; j < C - 1; j++) val += AL[cur[j]];
    ans = max(ans, val);
    return;
  }

  for (int j = 0; j < N; j++) {
    if (vis[j]) continue;
    vis[j] = true;
    cur.push_back(j);
    dfs(i + 1);
    cur.pop_back();
    vis[j] = false;
  }
}

void solve() {
  int M;
  cin >> N >> M;

  vector<vector<int>> A(N, vector<int>(M));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) cin >> A[i][j];
    int sum;

    sum = 0;
    for (int j = 0; j < M; j++) {
      sum += A[i][j];
      LL[i] = max(LL[i], sum);
    }

    sum = 0;
    for (int j = M - 1; j >= 0; j--) {
      sum += A[i][j];
      LR[i] = max(LR[i], sum);
    }
    AL[i] = sum;

    ll max_so_far = -INF, max_ending_here = 0;
    for (int j = 0; j < M; j++) {
      max_ending_here = max_ending_here + A[i][j];
      if (max_so_far < max_ending_here) max_so_far = max_ending_here;
      if (max_ending_here < 0) max_ending_here = 0;
    }
    PE[i] = max_so_far;
  }

  for (int i = 0; i < N; i++) ans = max(ans, PE[i]);
  for (C = 2; C <= N; C++) dfs(0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
