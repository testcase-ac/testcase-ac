#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N; string S;
  cin >> N >> S;

  int Lc = 0, Sc = 0;
  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (isdigit(S[i])) {
      ans++;
      continue;
    }
    if (S[i] == 'L') Lc++;
    if (S[i] == 'R') {
      if (Lc) ans++, Lc--;
      else break;
    }
    if (S[i] == 'S') Sc++;
    if (S[i] == 'K') {
      if (Sc) ans++, Sc--;
      else break;
    }

  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
