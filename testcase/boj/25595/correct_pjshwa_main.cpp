#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int A[MAX][MAX];

void solve() {
  int N;
  cin >> N;

  int si, sj;
  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    cin >> A[i][j];
    if (A[i][j] == 2) si = i, sj = j;
  }

  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    if (A[i][j] != 1) continue;
    if (((si + sj) & 1) != ((i + j) & 1)) continue;

    return cout << "Kiriya\n", void();
  }
  cout << "Lena\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
