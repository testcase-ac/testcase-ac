#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
string D[MAXN + 1];

void solve() {
  int N, L, K; string S; cin >> N >> L >> K >> S;
  sort(S.begin(), S.end());
  reverse(S.begin(), S.end());
  for (int i = 1; i <= N; ++i) D[i].resize(L, ' ');

  int ti = 1, j = 0;
  while (ti < K && j < L) {
    while (D[ti] != D[K]) ++ti;
    for (int i = ti; i <= K; ++i) D[i][j] = S.back(), S.pop_back();
    ++j;
  }
  while (j < L) D[K][j] = S.back(), S.pop_back(), ++j;

  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j < L; ++j) {
      if (D[i][j] == ' ') D[i][j] = S.back(), S.pop_back();
    }
    cout << D[i] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
