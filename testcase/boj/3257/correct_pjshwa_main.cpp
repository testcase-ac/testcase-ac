#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
int d[MAX + 1][MAX + 1];
string S, T, U;

bool r(int i, int j) {
  if (d[i][j] != -1) return d[i][j];
  if (i == S.size() && j == T.size()) return d[i][j] = 1;

  bool ret = 0;
  if (i < S.size() && S[i] == U[i + j]) ret |= r(i + 1, j);
  if (j < T.size() && T[j] == U[i + j]) ret |= r(i, j + 1);

  return d[i][j] = ret;
}

void solve() {
  cin >> S >> T >> U;

  memset(d, -1, sizeof(d));
  assert(r(0, 0));

  int i = 0, j = 0;
  while (i < S.size() || j < T.size()) {
    if (i < S.size() && S[i] == U[i + j] && d[i + 1][j]) {
      cout << 1;
      i++;
    }
    else {
      cout << 2;
      j++;
    }
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
