#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;
  vector<int> R(N), C(M);
  for (int i = 0; i < N; i++) {
    string S; cin >> S;
    for (int j = 0; j < M; j++) {
      if (S[j] == '1') {
        R[i] ^= 1;
        C[j] ^= 1;
      }
    }
  }

  int ro = accumulate(R.begin(), R.end(), 0), co = accumulate(C.begin(), C.end(), 0);
  if ((ro + co) & 1) return cout << "-1\n", void();

  int rz = N - ro, cz = M - co;
  if (rz & 1) cout << min(rz + cz, ro + co) << '\n';
  else cout << min(rz + co, ro + cz) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
