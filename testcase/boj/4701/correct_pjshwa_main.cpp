#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int N; string A[MAXN];

void solve() {
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N);

  int h = N / 2, j = 0;
  string S = A[h - 1], T = A[h], U = "";
  while (U.size() < S.size()) {
    char c = S[j];
    U += c;
    if (U >= S && U < T) break;
    if (c < 'Z') {
      U.back() = c + 1;
      if (U >= S && U < T) break;
      U.back() = c;
    }
    ++j;
  }
  cout << U << '\n';
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
