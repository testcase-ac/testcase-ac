#include <bits/stdc++.h> 
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, m;
  string s;
  cin >> n >> m >> s;

  int i = 0, score = 0;
  bool flag = false;
  while (i < m) {
    if (flag) {
      int streak = 0;
      while (i + 1 < m && s[i] == 'O' && s[i + 1] == 'I') {
        streak++;
        i += 2;
      }
      score += max(streak + 1 - n, 0);
      flag = false;
    }
    if (s[i] == 'I') flag = true;
    i++;
  }

  cout << score;
}
