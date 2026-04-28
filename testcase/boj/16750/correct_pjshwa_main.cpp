#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 2880;
int A[MAXV + 1], B[MAXV + 1];

void solve() {
  int N, M, x;
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> x, A[x] = 1;
  cin >> M;
  for (int i = 0; i < M; ++i) cin >> x, B[x] = 1;

  vector<int> W; int acnt = 0, bcnt = 0;
  for (int i = 1; i <= MAXV; ++i) {
    acnt += A[i]; bcnt += B[i];
    if (i == MAXV / 2) cout << acnt + bcnt << '\n';
    if (acnt == bcnt) continue;
    W.push_back(acnt < bcnt ? 2 : 1);
  }

  int tcnt = 0;
  for (int i = 1; i < W.size(); ++i) tcnt += W[i] != W[i - 1];
  cout << tcnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
