#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;

void solve() {
  int N; cin >> N;
  vector<tii> A(N);
  for (int i = 0; i < N; i++) {
    int t, s; cin >> t >> s;
    A[i] = {t, s, i + 1};
  }
  sort(A.begin(), A.end(), [](tii a, tii b) {
    auto [at, as, ai] = a; auto [bt, bs, bi] = b;

    int av = at * as + (at + bt) * bs;
    int bv = bt * bs + (at + bt) * as;
    if (av != bv) return av < bv;
    return ai < bi;
  });

  for (auto [t, s, i] : A) cout << i << ' ';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
