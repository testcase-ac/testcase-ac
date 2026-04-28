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

  string s, t;
  cin >> s >> t;
  int c = 0, si = 0, ti = 0;
  while (si < s.size()) {
    while (ti < t.size() && s[si] != t[ti]) {
      ti++;
      c++;
    }
    if (ti == t.size()) break;
    si++, ti++;
  }

  if (si == s.size()) cout << c + t.size() - ti << '\n';
  else cout << "IMPOSSIBLE\n";

}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  for (int i = 1; i <= t; i++) solve(i);
}
