#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size(), i = 0;

  int cnt = 0, chg = 0;
  string res = "";
  while (i < N) {
    char c = S[i];
    if (c == '@') chg++, cnt++, res += 'a';
    else if (c == '[') chg++, cnt++, res += 'c';
    else if (c == '!') chg++, cnt++, res += 'i';
    else if (c == ';') chg++, cnt++, res += 'j';
    else if (c == '^') chg++, cnt++, res += 'n';
    else if (c == '0') chg++, cnt++, res += 'o';
    else if (c == '7') chg++, cnt++, res += 't';
    else if (c == '\\') {
      chg++, cnt++;
      if (S[i + 1] == '\'') i++, res += 'v';
      else i += 2, res += 'w';
    }
    else cnt++, res += c;
    i++;
  }

  if (chg * 2 >= cnt) cout << "I don't understand\n";
  else cout << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
