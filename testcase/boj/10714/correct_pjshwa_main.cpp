#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
ll A[MAX], d[MAX][MAX][2];
int N;

int pre(int i) {
  if (i == 0) return N - 1;
  else return i - 1;
}

int nxt(int i) {
  if (i == N - 1) return 0;
  else return i + 1;
}

ll rec(int l, int r, int p) {
  if (d[l][r][p] != -1) return d[l][r][p];

  if (l == r) {
    if (p) return d[l][r][p] = 0;
    else return d[l][r][p] = A[l];
  }

  ll ret = 0;
  if (p) {
    if (A[l] > A[r]) ret = rec(nxt(l), r, 0);
    else ret = rec(l, pre(r), 0);
  }
  else {
    ret = max(ret, A[l] + rec(nxt(l), r, 1));
    ret = max(ret, A[r] + rec(l, pre(r), 1));
  }
  return d[l][r][p] = ret;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  memset(d, -1, sizeof(d));
  ll ans = 0;
  for (int i = 0; i < N; i++) {
    ans = max(ans, A[i] + rec(nxt(i), pre(i), 1));
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
