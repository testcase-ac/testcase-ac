#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100, MAXS = 1e4;
int N, S[MAXN], E[MAXN], L[MAXN];
int dp[MAXN][MAXS + 1];

int rec(int i, int s) {
  if (i == N) return 0;
  if (dp[i][s] != -1) return dp[i][s];

  int ret = rec(i + 1, s);
  ret = max(ret, rec(i + 1, s + S[i]) + max(0, E[i] - s * L[i]));
  return dp[i][s] = ret;
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int pre = 0; cin >> N;
  vector<tuple<int, int, int>> A;
  for (int i = 0; i < N; ++i) {
    int s, e, l; cin >> s >> e >> l;
    if (l == 0) pre += e;
    else A.emplace_back(s, e, l);
  }
  sort(A.begin(), A.end(), [](auto &a, auto &b) {
    auto [as, ae, al] = a; auto [bs, be, bl] = b;
    return as * bl < bs * al;
  });

  N = A.size();
  for (int i = 0; i < N; ++i) tie(S[i], E[i], L[i]) = A[i];

  memset(dp, -1, sizeof(dp));
  cout << pre + rec(0, 0) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
