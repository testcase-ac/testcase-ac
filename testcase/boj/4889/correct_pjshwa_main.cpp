#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S; int tc;
void solve() {
  cout << ++tc << ". ";

  int N = S.size(), ans = 0, dt = 0;
  for (int i = 0; i < N; i++) {
    if (S[i] == '{') {
      if (N - i == dt) ans++, dt--;
      else dt++;
    }
    else {
      if (dt) dt--;
      else ans++, dt++;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> S) {
    if (S[0] == '-') break;
    solve();
  }
}
