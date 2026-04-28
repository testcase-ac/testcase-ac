#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100, INF = 0x3f3f3f3f;
int A[MAX], d[1 << 15][2][31];
int N;

int r(int s, int o, int t) {
  if (d[s][o][t] != -1) return d[s][o][t];
  if (t == 30) return d[s][o][t] = INF;
  if (o == 1 && s == (1 << N) - 1) return d[s][o][t] = 0;

  int ret = INF;
  for (int i = 0; i < N; i++) {
    int ci = (s >> i) & 1;
    if (o != ci) continue;
    ret = min(ret, r(s ^ (1 << i), o ^ 1, t + 1) + A[i]);

    for (int j = i + 1; j < N; j++) {
      int cj = (s >> j) & 1;
      if (o != cj || A[i] == A[j]) continue;
      int ns = s ^ (1 << i) ^ (1 << j);
      ret = min(ret, r(ns, o ^ 1, t + 1) + max(A[i], A[j]));
    }
  }
  return d[s][o][t] = ret;
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A, A + N); memset(d, -1, sizeof(d));

  int ans = r(0, 0, 0);
  if (ans == INF) ans = -1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
