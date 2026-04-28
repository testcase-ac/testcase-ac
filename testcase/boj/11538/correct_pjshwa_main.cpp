#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXB = 18, MAXL = 1e6;
int P[MAXL + 1];

void solve() {
  int L;
  vector<int> A;
  while (cin >> L) {
    if (L == -1) break;
    A.push_back(L); P[L] = 1;
  }

  for (int e : A) {
    int cnt = 0;
    for (int b1 = 0; b1 < MAXB; ++b1) {
      int t = e ^ (1 << b1);
      if (t <= e || !P[t]) continue;
      ++cnt;
    }
    for (int b1 = 0; b1 < MAXB; ++b1) for (int b2 = b1 + 1; b2 < MAXB; ++b2) {
      int t = e ^ (1 << b1) ^ (1 << b2);
      if (t <= e || !P[t]) continue;
      ++cnt;
    }
    cout << e << ':' << cnt << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
