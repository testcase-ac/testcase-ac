#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool ocv[26];
bool tcv[26][26];
int main() {
  fast_io();

  char board[3][4];
  for (int i = 0; i < 3; i++) cin >> board[i];

  for (int i = 0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) ocv[board[i][0] - 'A'] = true;
    if (board[i][0] == board[i][1] && board[i][1] != board[i][2]) tcv[board[i][0] - 'A'][board[i][2] - 'A'] = true;
    if (board[i][0] == board[i][2] && board[i][1] != board[i][2]) tcv[board[i][0] - 'A'][board[i][1] - 'A'] = true;
    if (board[i][0] != board[i][1] && board[i][1] == board[i][2]) tcv[board[i][0] - 'A'][board[i][2] - 'A'] = true;

    if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) ocv[board[0][i] - 'A'] = true;
    if (board[0][i] == board[1][i] && board[1][i] != board[2][i]) tcv[board[0][i] - 'A'][board[2][i] - 'A'] = true;
    if (board[0][i] == board[2][i] && board[1][i] != board[2][i]) tcv[board[0][i] - 'A'][board[1][i] - 'A'] = true;
    if (board[0][i] != board[1][i] && board[1][i] == board[2][i]) tcv[board[0][i] - 'A'][board[2][i] - 'A'] = true;
  }

  // Diagonals
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) ocv[board[0][0] - 'A'] = true;
  if (board[0][0] == board[1][1] && board[1][1] != board[2][2]) tcv[board[0][0] - 'A'][board[2][2] - 'A'] = true;
  if (board[0][0] == board[2][2] && board[1][1] != board[2][2]) tcv[board[0][0] - 'A'][board[1][1] - 'A'] = true;
  if (board[0][0] != board[1][1] && board[1][1] == board[2][2]) tcv[board[0][0] - 'A'][board[2][2] - 'A'] = true;

  if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) ocv[board[0][2] - 'A'] = true;
  if (board[0][2] == board[1][1] && board[1][1] != board[2][0]) tcv[board[0][2] - 'A'][board[2][0] - 'A'] = true;
  if (board[0][2] == board[2][0] && board[1][1] != board[2][0]) tcv[board[0][2] - 'A'][board[1][1] - 'A'] = true;
  if (board[0][2] != board[1][1] && board[1][1] == board[2][0]) tcv[board[0][2] - 'A'][board[2][0] - 'A'] = true;

  int fv = 0, tv = 0;
  for (int i = 0; i < 26; i++) {
    if (ocv[i]) fv++;
    for (int j = i + 1; j < 26; j++) {
      if (tcv[i][j] || tcv[j][i]) tv++;
    }
  }
  cout << fv << '\n' << tv << '\n';
}
