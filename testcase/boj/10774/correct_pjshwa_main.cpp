#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int z2v(string O) {
  if (O == "S") return 0;
  if (O == "M") return 1;
  if (O == "L") return 2;
  return -1;
}

void solve() {
  int N, M;
  cin >> N >> M;

  vector<int> R(N + 1), A(N + 1, 3);
  for (int i = 1; i <= N; i++) {
    string O; cin >> O;
    R[i] = z2v(O);
  }
  for (int j = 1; j <= M; j++) {
    string O; int i; cin >> O >> i;
    A[i] = min(A[i], z2v(O));
  }

  int ans = 0;
  for (int i = 1; i <= N; i++) {
    if (R[i] >= A[i]) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
