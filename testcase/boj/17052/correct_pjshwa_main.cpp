#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  int xi;
  for (int i = 0; i < N; i++) {
    if (S[i] == 'x') xi = i;
  }

  for (S[xi] = '0'; S[xi] <= '9'; S[xi]++) {
    int sum = 0;
    for (int i = 1; i < N; i++) {
      int c = S[N - 1 - i] - '0';
      if (i & 1) {
        c *= 2;
        if (c >= 10) c = c % 10 + 1;
      }
      sum += c;
    }
    int chk = (sum * 9) % 10;
    if (S[N - 1] - '0' == chk) {
      cout << S[xi] << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
