#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
char board[MAX + 1][MAX + 1];
int pj[MAX + 1][MAX + 1], po[MAX + 1][MAX + 1], pi[MAX + 1][MAX + 1];

void solve(int tc) {
  cout << "Case #" << tc << ": ";

  string s;
  cin >> s;
  int n = s.size(), m = 0;
  for (int i = 0; i < n; i++) {
    m = (m + (s[i] - '0')) % 9;
  }

  if (m == 0) {
    cout << s[0] << 0;
    for (int i = 1; i < n; i++) cout << s[i];
    cout << '\n';
  }
  else {
    m = 9 - m;

    bool used = false;
    for (int i = 0; i < n; i++) {
      if (!used && m < s[i] - '0') {
        cout << m;
        used = true;
      }
      cout << s[i];
    }
    if (!used) cout << m;
    cout << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  for (int i = 1; i <= t; i++) solve(i);
}
