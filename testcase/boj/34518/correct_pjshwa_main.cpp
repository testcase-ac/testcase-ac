#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5000;
int A[2][MAXN];

void solve() {
  int N, i = 0; cin >> N;
  int oN = N;

  int mod = N % 4;
  if (mod == 2 || mod == 3) return cout << "-1\n", void();

  while (N >= 4) {
    A[0][i] = A[1][oN - 1 - i] = N;
    A[1][i] = A[0][oN - 2 - i] = N - 1;
    A[0][i + 1] = A[0][oN - 1 - i] = N - 2;
    A[1][i + 1] = A[1][oN - 2 - i] = N - 3;
    N -= 4; i += 2;
  }
  if (N == 1) A[0][i] = A[1][i] = 1;

  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < oN; ++j) {
      cout << A[i][j] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
