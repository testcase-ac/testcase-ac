#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;

void solve() {
  int N;
  cin >> N;
  vector<pii> A(N);
  for (int i = 0; i < N; i++) {
    int x; string t;
    cin >> x >> t;
    if (t == "W") A[i] = {x, 1};
    else A[i] = {x, -1};
  }
  sort(A.begin(), A.end());

  int ans = 0;
  for (int s = 0; s < 2; s++) {
    map<int, int> t;

    int dt = 0;
    for (int i = s; i + 1 < N; i += 2) {
      auto [x1, d1] = A[i];
      auto [x2, d2] = A[i + 1];
      dt += (d1 + d2);

      t[dt] = i + 1;
    }

    int fk = t.rbegin()->first, prv = 0;
    while (fk >= -MAX) {
      t[fk] = max(t[fk], prv);
      prv = t[fk];
      fk -= 2;
    }

    dt = 0;
    for (int i = s; i + 1 < N; i += 2) {
      if (t.count(dt)) {
        int x1 = A[i].first;
        int x2 = A[t[dt]].first;
        ans = max(ans, x2 - x1);
      }

      auto [x1, d1] = A[i];
      auto [x2, d2] = A[i + 1];
      dt += (d1 + d2);
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
