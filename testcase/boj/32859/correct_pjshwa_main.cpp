#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, S; cin >> N >> M >> S;

  vector<pii> A;
  for (int i = 0; i < M; ++i) {
    int a, t; cin >> a >> t;
    A.emplace_back(a, t);
  }

  vector<int> B;
  for (int p = 1; p <= N; ++p) {
    int sta = -1, by = 0, f = 0;
    for (int i = 0; i < M; ++i) {
      auto [a, t] = A[i];
      if (a == p) {
        if (t == 1) sta = i;
        else {
          if (sta != -1 && by >= S) B.push_back(p);
          f = 1;
          break;
        }
      }
      else if (sta != -1 && t == 0) ++by;
    }
    if (f == 0 && sta != -1 && by >= S) B.push_back(p);
  }

  if (B.empty()) cout << "-1\n";
  else for (int b : B) cout << b << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
