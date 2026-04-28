#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M;
  cin >> N >> M;

  int P = 1;
  for (int i = 0; i < N - 1; i++) {
    int L = 0, R = M + 1;

    int k; cin >> k;
    while (k--) {
      string d; int p;
      cin >> p >> d;
      if (d == "L") L = max(L, p);
      else R = min(R, p);
    }

    if (L >= R) {
      if (P < R) continue;
      else P = max(P, L + 1);
    }
    else if (R == L + 1) P = M + 1;
    else {
      if (P >= R) P = M + 1;
      else P = max(P, L + 1);
    }
  }

  if (P == M + 1) cout << "NO\n";
  else cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
