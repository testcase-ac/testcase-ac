#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool has_dup(int n) {
  string s = to_string(n);
  sort(s.begin(), s.end());
  return unique(s.begin(), s.end()) != s.end();
}

bool has_zero(int n) {
  string s = to_string(n);
  return find(s.begin(), s.end(), '0') != s.end();
}

void solve() {
  int N; cin >> N;
  vector<tuple<string, int, int>> P;
  for (int i = 0; i < N; i++) {
    string a; int b, c; cin >> a >> b >> c;
    P.emplace_back(a, b, c);
  }

  int ans = 0;
  for (int i = 123; i <= 987; i++) {
    if (has_dup(i) || has_zero(i)) continue;

    string s = to_string(i); int f = 1;
    for (auto [t, b, c] : P) {
      int strike = 0, ball = 0;
      for (int j = 0; j < 3; j++) {
        if (s[j] == t[j]) strike++;
        else if (s[j] == t[(j + 1) % 3] || s[j] == t[(j + 2) % 3]) ball++;
      }

      if (!(strike == b && ball == c)) f = 0;
    }
    ans += f;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
