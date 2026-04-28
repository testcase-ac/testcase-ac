#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int A[MAX + 10], B[MAX + 10], P1[MAX + 10], P2[MAX + 10];

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; i++) cin >> A[i];
  for (int i = 1; i <= M; i++) cin >> B[i];

  for (int i = N; i >= 1; i--) P1[i] += P1[i + 1] + A[i];
  for (int i = M; i >= 1; i--) P2[i] += P2[i + 1] + B[i];

  int minz = min(N - P1[1], M - P2[1]), i = 1, j = 1;
  int ans = min(P1[1], P2[1]);
  for (int z = 1; z <= minz; z++) {
    while (i <= N && A[i] == 1) i++;
    while (j <= M && B[j] == 1) j++;

    int az = z + P1[i], bz = z + P2[j];
    ans = max(ans, min(az, bz));
    i++, j++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
