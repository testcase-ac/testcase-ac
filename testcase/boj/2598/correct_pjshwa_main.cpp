#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int D[6][4] = {
  {1, 4, 3, 5},
  {0, 5, 2, 4},
  {1, 5, 3, 4},
  {0, 4, 2, 5},
  {0, 1, 2, 3},
  {0, 3, 2, 1}
};

int c2i(char c) {
  if (c == 'R') return 0;
  if (c == 'G') return 1;
  if (c == 'B') return 2;
  if (c == 'Y') return 3;

  assert(false);
  return -1;
}

ll A[4][6], B[4][4], T;
set<ll> U;

ll gen_num() {

  // check valid
  for (int j = 0; j < 4; ++j) {
    int l = 0;
    for (int i = 0; i < 4; ++i) l |= (1 << B[i][j]);
    if (__builtin_popcount(l) != 4) return -1;
  }

  vector<vector<int>> R; vector<int> v0;
  for (int j = 0; j < 4; ++j) {
    int l = 0;
    for (int i = 0; i < 4; ++i) l = 4 * l + B[i][j];
    v0.push_back(l);
  }
  for (int i = 0; i < 4; ++i) {
    R.push_back(v0);
    rotate(v0.begin(), v0.begin() + 1, v0.end());
  }
  sort(R.begin(), R.end());

  ll ret = 0;
  for (int j = 0; j < 4; ++j) ret = 256 * ret + R[0][j];
  ret |= A[3][T] << 32;
  return ret;
}

void dfs(int i) {
  if (i == 4) {
    ll num = gen_num();
    if (num != -1) U.insert(num);
  }
  else {
    for (int t = 0; t < 6; ++t) for (int fw = 0; fw < 4; ++fw) {
      for (int j = 0; j < 4; ++j) B[i][j] = A[i][D[t][(j + fw) % 4]];
      T = t; dfs(i + 1);
    }
  }
}

void solve() {
  string S;
  for (int i = 0; i < 4; ++i) {
    cin >> S;
    for (int j = 0; j < 6; ++j) A[i][j] = c2i(S[j]);
  }

  dfs(0);
  cout << U.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
