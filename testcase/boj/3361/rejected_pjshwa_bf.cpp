#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  int iter = -1, swap_cnt = 0;
  while (1) {
    ++iter;

    bool change = false;
    for (int i = 0; i < N - 1; ++i) {
      if (S[i] == 'R' && S[i + 1] == 'L') {
        swap(S[i], S[i + 1]);
        change = true;
        ++i;
        ++swap_cnt;
      }
    }
    if (!change) break;
    // cout << S << '\n'; // "S =
  }

  cout << iter << ' ' << swap_cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
