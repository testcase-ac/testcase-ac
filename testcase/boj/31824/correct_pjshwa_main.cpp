#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M; cin >> N >> M;

  map<string, string> B;
  for (int i = 0; i < N; ++i) {
    string Q, A; cin >> Q >> A;
    B[Q] = A;
  }

  for (int i = 0; i < M; ++i) {
    string Q; cin >> Q; int Z = Q.size(), f = 0;
    for (int i = 0; i < Z; ++i) {
      string cur = "";
      for (int j = 0; j < 10 && i + j < Z; ++j) {
        cur += Q[i + j];
        if (B.count(cur)) {
          cout << B[cur];
          f = 1;
        }
      }
    }
    if (!f) cout << -1;
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
