#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int N, M;
vector<int> v1, v2;

void solve() {
  v1.resize(N);
  v2.resize(M);
  for (int i = 0; i < N; i++) cin >> v1[i];
  for (int i = 0; i < M; i++) cin >> v2[i];

  int p1 = 0, ans = 0;
  for (int p2 = 0; p2 < M; p2++) {
    while (p1 < N && v1[p1] < v2[p2]) p1++;
    if (v1[p1] == v2[p2]) ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> N >> M;
    if (N == 0 && M == 0) break;
    solve();
  }
}
