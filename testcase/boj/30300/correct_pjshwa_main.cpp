#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  
  int mmex = 1, mask = 0, ans = 0;
  for (int b = 0; b < 30; ++b) {
    mask |= (1 << b);

    set<int> U;
    for (int i = 0; i < N; ++i) U.insert(A[i] & mask);

    // calculate mex
    vector<int> V;
    for (int x : U) V.push_back(x);

    int mex = 0;
    while (mex < (int)V.size() && V[mex] == mex) ++mex;
    if (mex > mmex) ans = mask, mmex = mex;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
