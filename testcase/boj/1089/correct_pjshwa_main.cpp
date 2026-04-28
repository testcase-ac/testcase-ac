#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll pow(ll a, ll b) {
  ll ret = 1;
  for (; b; b >>= 1, a = (a * a))
    if (b & 1) ret = (ret * a);
  return ret;
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

char board[5][36];
int values[9];
int cases[9];
int main() {
  fast_io();

  int n, st_pos, initial, case_cnt;
  set<int> imp;
  cin >> n;

  for (int i = 0; i < 5; i++) cin >> board[i];
  for (int i = 0; i < n; i++) {
    st_pos = 4 * i;
    imp.clear();

    if (board[0][st_pos + 0] == '#') imp.insert(1);
    if (board[0][st_pos + 1] == '#') {
      imp.insert(1); imp.insert(4);
    }
    // if (board[0][st_pos + 2] == '#') imp.insert(1);
    if (board[1][st_pos + 0] == '#') {
      imp.insert(1); imp.insert(2); imp.insert(3); imp.insert(7);
    }
    if (board[1][st_pos + 1] == '#') {
      for (int j = 0; j < 10; j++) imp.insert(j);
    }
    if (board[1][st_pos + 2] == '#') {
      imp.insert(5); imp.insert(6);
    }
    if (board[2][st_pos + 0] == '#') {
      imp.insert(1); imp.insert(7);
    }
    if (board[2][st_pos + 1] == '#') {
      imp.insert(0); imp.insert(1); imp.insert(7);
    }
    // if (board[2][st_pos + 2] == '#') imp.insert(1);
    if (board[3][st_pos + 0] == '#') {
      imp.insert(1); imp.insert(3); imp.insert(4); imp.insert(5); imp.insert(7); imp.insert(9);
    }
    if (board[3][st_pos + 1] == '#') {
      for (int j = 0; j < 10; j++) imp.insert(j);
    }
    if (board[3][st_pos + 2] == '#') imp.insert(2);
    if (board[4][st_pos + 0] == '#') {
      imp.insert(1); imp.insert(4); imp.insert(7);
    }
    if (board[4][st_pos + 1] == '#') {
      imp.insert(1); imp.insert(4); imp.insert(7);
    }
    // if (board[4][st_pos + 2] == '#') imp.insert(1);

    initial = 45;
    case_cnt = 10;
    for(auto el : imp) {
      initial -= el;
      case_cnt--;
    }

    if (!initial) {
      cout << "-1\n";
      return 0;
    }

    values[i] = initial;
    cases[i] = case_cnt;
  }

  ll total_cases = 1, total_sum = 0;
  for (int i = 0; i < n; i++) total_cases *= cases[i];
  for (int i = 0; i < n; i++) {
    total_sum += (values[i] * pow(10, n - i - 1) * (total_cases / cases[i]));
  }

  cout << fixed << setprecision(6) << (double)total_sum / total_cases << '\n';
}
