#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char board[1001][1001];

int main() {
  fast_io();

  int ni, mj;
  cin >> ni >> mj;
  for (int i = 0; i < ni; i++) cin >> board[i];

  int streak_gcd_w = mj;
  for (int i = 0; i < ni; i++) {
    char schar = board[i][0];
    int streak = 0;
    for (int j = 0; j < mj; j++) {
      if (board[i][j] == schar) streak++;
      else {
        schar = board[i][j];
        streak_gcd_w = gcd(streak_gcd_w, streak);
        streak = 1;
      }
    }
    streak_gcd_w = gcd(streak_gcd_w, streak);
  }

  int streak_gcd_h = ni;
  for (int j = 0; j < mj; j++) {
    char schar = board[0][j];
    int streak = 0;
    for (int i = 0; i < ni; i++) {
      if (board[i][j] == schar) streak++;
      else {
        schar = board[i][j];
        streak_gcd_h = gcd(streak_gcd_h, streak);
        streak = 1;
      }
    }
    streak_gcd_h = gcd(streak_gcd_h, streak);
  }

  cout << ni / streak_gcd_h << ' ' << mj / streak_gcd_w << '\n';
  for (int i = 0; i < ni; i += streak_gcd_h) {
    for (int j = 0; j < mj; j += streak_gcd_w) cout << board[i][j];
    cout << '\n';
  }
}
