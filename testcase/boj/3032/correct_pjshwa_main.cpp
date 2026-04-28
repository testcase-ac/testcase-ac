#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int A[MAX], N, O;
int d[MAX][MAX][MAX][2];

int prv(int x) {
  return (x + N - 1) % N;
}

int nxt(int x) {
  return (x + 1) % N;
}

int rec(int l, int r, int o, int p) {
  if (d[l][r][o][p] != -1) return d[l][r][o][p];

  bool ret = false, oddl = (A[l] & 1), oddr = (A[r] & 1);
  if (l == r) {
    if (p && oddl) o++;
    ret = (o > O - o) ^ !p;
  }
  else {
    ret |= !rec(nxt(l), r, o + (oddl && p), 1 - p);
    ret |= !rec(l, prv(r), o + (oddr && p), 1 - p);
  }
  return d[l][r][o][p] = ret;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i], O += (A[i] & 1);

  int ans = 0;
  memset(d, -1, sizeof(d));
  for (int i = 0; i < N; i++) {
    ans += !rec(nxt(i), prv(i), (A[i] & 1), 0);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
