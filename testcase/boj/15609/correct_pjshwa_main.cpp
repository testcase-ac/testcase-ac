#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN];
double dp[MAXN][13];

// probability of i-th player winning at o-th round
double rec(int i, int o) {
  if (o == -1) return 1;
  if (dp[i][o] != -1) return dp[i][o];

  int B = 1 << o; double p = 0;
  for (int s = 0; s < B; ++s) {
    int j = i & ~(B - 1); j |= s; j ^= B;
    double wp = A[i] == A[j] ? 0.5 : (double)A[i] / (A[i] + A[j]);
    p += rec(j, o - 1) * wp;
  }
  return dp[i][o] = p * rec(i, o - 1);
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A + 1, A + N);

  int p = 1, o = 0;
  while (p < N) p <<= 1, ++o;

  int def = p - N;
  vector<int> B;
  for (int i = 0; i < N; ++i) {
    B.push_back(A[i]);
    if (def) B.push_back(0), --def;
  }
  N = B.size();
  for (int i = 0; i < N; ++i) {
    A[i] = B[i];
    fill(dp[i], dp[i] + 13, -1);
  }

  cout << fixed << setprecision(10) << rec(0, o - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
