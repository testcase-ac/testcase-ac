#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

const int MAXN = 1e5;
int G[MAXN + 1];

void solve() {
  int N; cin >> N;

  for (int g = 3; g <= N; ++g) {
    vector<int> Gs;
    for (int q = 2;; ++q) {
      int sum = q * (q + 1) / 2;
      int rem = g - sum;
      if (rem < 0) break;
      if (rem % q) continue;

      int add = rem / q, val = 0;
      for (int i = 1; i <= q; ++i) val ^= G[add + i];
      Gs.push_back(val);
    }
    compress(Gs);

    // calculate mex of Gs
    int mex = 0;
    for (int g : Gs) {
      if (g == mex) ++mex;
    }
    G[g] = mex;
  }

  int val = G[N];
  if (val == 0) return cout << "-1\n", void();

  for (int q = 2;; ++q) {
    int sum = q * (q + 1) / 2;
    int rem = N - sum;
    if (rem < 0) break;
    if (rem % q) continue;

    int add = rem / q, val = 0;
    for (int i = 1; i <= q; ++i) val ^= G[add + i];
    if (val == 0) return cout << q << '\n', void();
  }
}
 
int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
