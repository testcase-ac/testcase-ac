#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
ld dp[MAXN + 1][MAXN + 1];
pii A[MAXN + 1]; int N;

ld dist(pii a, pii b) {
  return sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

ld rec(int i, int j) {
  if (dp[i][j] != -1) return dp[i][j];
  if (i == N && j == N) return dp[i][j] = 0;
  if (i == N) return dp[i][j] = rec(i, j + 1) + dist(A[j], A[j + 1]);
  if (j == N) return dp[i][j] = rec(i + 1, j) + dist(A[i], A[i + 1]);

  vector<pii> next_p;
  if (i < j) next_p = {pii{j + 1, j}, pii{i, j + 1}};
  else next_p = {pii{i + 1, j}, pii{i, i + 1}};

  ld ret = 1e18;
  for (auto [ni, nj] : next_p) {
    if (ni > N || nj > N) continue;
    ld d = dist(A[i], A[ni]) + dist(A[j], A[nj]);
    ret = min(ret, rec(ni, nj) + d);
  }
  return dp[i][j] = ret;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; ++i) {
    int x, y; cin >> x >> y;
    A[i] = {x, y};
  }
  sort(A + 1, A + N + 1);

  for (int i = 1; i <= N; ++i) for (int j = 1; j <= N; ++j) dp[i][j] = -1;
  cout << fixed << setprecision(2) << rec(1, 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
