#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, D; string S; cin >> N >> D >> S;

  int f = 0, l = -1;
  for (int j = 0; j < N; ++j) {
    char c = S[j];
    if (f == 0) {
      if (c == 'w') f = 1, l = j;
    }
    else {
      if (c == 'h') {
        if (j - D <= l) {
          swap(S[j], S[l]);
          ++l;
        }
        else {
          swap(S[j], S[j - D]);
        }
      }
      else if (c != 'w') f = 0;
    }
  }
  cout << S << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
