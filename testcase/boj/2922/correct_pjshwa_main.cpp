#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_vowel(char c) {
  return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

ll d[101][3][3][2];

void solve() {
  string S; int N;
  cin >> S; N = S.size();

  d[0][0][0][0] = 1;
  for (int i = 1; i <= N; i++) {
    char cchar = S[i - 1];
    for (int vc = 0; vc < 3; vc++) for (int cc = 0; cc < 3; cc++) {
      for (char nchar = 'A'; nchar <= 'Z'; nchar++) {
        if (cchar != '_' && cchar != nchar) continue;
        if (vc == 2 && is_vowel(nchar)) continue;
        if (cc == 2 && !is_vowel(nchar)) continue;

        if (nchar == 'L') {
          d[i][0][cc + 1][1] += d[i - 1][vc][cc][0];
          d[i][0][cc + 1][1] += d[i - 1][vc][cc][1];
        }
        else if (is_vowel(nchar)) {
          d[i][vc + 1][0][0] += d[i - 1][vc][cc][0];
          d[i][vc + 1][0][1] += d[i - 1][vc][cc][1];
        }
        else {
          d[i][0][cc + 1][0] += d[i - 1][vc][cc][0];
          d[i][0][cc + 1][1] += d[i - 1][vc][cc][1];
        }
      }
    }
  }

  ll ans = 0;
  for (int vc = 0; vc < 3; vc++) for (int cc = 0; cc < 3; cc++) {
    ans += d[N][vc][cc][1];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
