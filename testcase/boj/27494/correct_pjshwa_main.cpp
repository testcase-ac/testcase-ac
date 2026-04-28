#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int ans = 0;
  for (int i = 1; i <= N; i++) {
    string s = to_string(i);

    int state = 0;
    for (char& c : s) {
      if (state == 0 && c == '2') state = 1;
      else if (state == 1 && c == '0') state = 2;
      else if (state == 2 && c == '2') state = 3;
      else if (state == 3 && c == '3') state = 4;
    }
    if (state == 4) ans++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
