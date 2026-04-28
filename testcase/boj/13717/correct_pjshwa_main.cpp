#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int msum = 0, mmax = 0; string mp;
  for (int i = 0; i < N; i++) {
    string P; int K, M, cur = 0; cin >> P >> K >> M;
    while (M >= K) M -= K, M += 2, cur++;

    msum += cur;
    if (cur > mmax) mmax = cur, mp = P;
  }
  cout << msum << "\n" << mp << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
