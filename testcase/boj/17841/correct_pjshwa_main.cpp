#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, MOD = 1e9 + 7;
const string t = "UNIST";
ll d[MAX][5];
string words[MAX];

int match_s(string s, int spos) {
  for (int i = min(5, (int)s.size()); i >= 1; i--) {
    if (s.substr(0, i) == t.substr(spos, i)) return i;
  }
  return 0;
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> words[i];

  int ss;
  ss = match_s(words[0], 0);
  for (int j = 0; j < ss; j++) d[0][j] = 1;

  for (int i = 1; i < n; i++) {
    for (int j = 0; j < 5; j++) d[i][j] = d[i - 1][j];

    ss = match_s(words[i], 0);
    for (int j = 0; j < ss; j++) d[i][j] = (d[i][j] + 1) % MOD;

    for (int spos = 1; spos <= 4; spos++) {
      ss = match_s(words[i], spos);
      for (int j = 0; j < ss; j++) d[i][spos + j] = (d[i][spos + j] + d[i - 1][spos - 1]) % MOD;
    }
  }

  cout << d[n - 1][4];
}
