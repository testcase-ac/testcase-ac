#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tally[7][7];

int atox(char c) {
  if (c == 'B') return 0;
  if (c == 'E') return 1;
  if (c == 'S') return 2;
  if (c == 'I') return 3;
  if (c == 'G') return 4;
  if (c == 'O') return 5;
  if (c == 'M') return 6;
}

ll ans = 0;
vector<int> cur;

void dfs(int i) {
  if (i == 7) {
    int res = cur[0] + 2 * cur[1] + 2 * cur[2] + cur[3];
    res *= (cur[1] + cur[2] + cur[4] + cur[5]);
    res *= (2 * cur[5] + cur[6]);

    if (res % 7 == 0) {
      ll addend = 1;
      for (int j = 0; j < 7; j++){
        addend *= tally[j][cur[j]];
      }
      ans += addend;
    }
    return;
  }

  for (int j = 0; j < 7; j++) {
    cur.push_back(j);
    dfs(i + 1);
    cur.pop_back();
  }
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s;
    int x;
    cin >> s >> x;
    tally[atox(s[0])][(x + 100'002) % 7]++;
  }

  dfs(0);
  cout << ans << '\n';
}
