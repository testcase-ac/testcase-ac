#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50, MOD = 1e9 + 7;
string A, B, C;
int N, d[MAX][2][10][10];

int r(int i, int carry, int az, int bz) {
  if (i == N) return carry == 0;
  if (d[i][carry][az][bz] != -1) return d[i][carry][az][bz];

  int alb = 0, aub = 9, blb = 0, bub = 9;
  if (i == N - 1) alb = blb = 1;
  if (A[i] != '?') alb = aub = A[i] - '0';
  if (B[i] != '?') blb = bub = B[i] - '0';

  int res = 0;
  for (int ai = alb; ai <= aub; ai++) for (int bi = blb; bi <= bub; bi++) {
    int ci = ai + bi + carry;
    if (C[i] == '?' || ci % 10 == C[i] - '0') res = (res + r(i + 1, ci / 10, ai, bi)) % MOD;
  }

  return d[i][carry][az][bz] = res;
}

void solve() {
  reverse(A.begin(), A.end());
  reverse(B.begin(), B.end());
  reverse(C.begin(), C.end());
  N = C.size();

  memset(d, -1, sizeof(d));
  cout << r(0, 0, 0, 0) << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> A;
    if (A == "0") break;
    cin >> B >> C;
    solve();
  }
}
