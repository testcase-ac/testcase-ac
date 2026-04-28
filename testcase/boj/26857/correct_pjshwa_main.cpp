#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000, INF = 0x3f3f3f3f;
char board[MAX + 1][MAX + 1];

void solve() {
  int R, C; cin >> R >> C;

  int T[27]{}; int total = 0;
  for (int i = 0; i < R; ++i) {
    cin >> board[i];
    for (int j = 0; j < C; ++j) {
      if (board[i][j] == '.') continue;
      ++T[board[i][j] - 'a' + 1];
      ++total;
    }
  }

  vector<vector<bool>> U(27, vector<bool>(total + 1, false));
  U[0][0] = true;
  for (int i = 1; i <= 26; ++i) {
    for (int j = 0; j <= total; ++j) U[i][j] = U[i - 1][j];
    for (int j = T[i]; j <= total; ++j) {
      U[i][j] = U[i][j] || U[i - 1][j - T[i]];
    }
  }

  int S = 0;
  for (int i = total / 2; i >= 0; --i) {
    if (!U[26][i]) continue;
    S = i;
    break;
  }

  // backtrack
  vector<int> groupA, groupB;
  int i = 26, j = S;
  while (i > 0 || j > 0) {
    if (T[i] == 0) {}
    else if (j >= T[i] && U[i - 1][j - T[i]]) {
      groupA.push_back(i);
      j -= T[i];
    }
    else groupB.push_back(i);
    --i;
  }

  vector<char> charA, charB;
  for (int i : groupA) {
    char c = 'a' + i - 1;
    for (int j = 0; j < T[i]; ++j) charA.push_back(c);
  }
  for (int i : groupB) {
    char c = 'a' + i - 1;
    for (int j = 0; j < T[i]; ++j) charB.push_back(c);
  }
  if (charA.size() < charB.size()) swap(charA, charB);

  int msize = INF, mR, mC;
  for (int aR = 0; aR <= MAX; ++aR) for (int aC = 0;; ++aC) {
    int nR = R + aR, nC = C + aC;
    if (nR * nC > 2 * R * C) break;

    int z1, z2;
    z1 = z2 = (nR * nC) / 2;
    if ((nR * nC) % 2 == 1) ++z1;

    if (z1 < charA.size() || z2 < charB.size()) continue;

    if (msize > nR * nC) {
      msize = nR * nC;
      mR = nR, mC = nC;
    }
  }

  cout << mR << " " << mC << "\n";
  for (int i = 0; i < mR; ++i) {
    for (int j = 0; j < mC; ++j) {
      if ((i + j) % 2 == 0) {
        if (charA.empty()) cout << ".";
        else {
          cout << charA.back();
          charA.pop_back();
        }
      }
      else {
        if (charB.empty()) cout << ".";
        else {
          cout << charB.back();
          charB.pop_back();
        }
      }
    }
    cout << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
