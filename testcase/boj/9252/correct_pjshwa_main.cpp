#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int lcs[1001][1001];
void trace(int i, int j, int n, string &s2) {
  if (n == 0) return;
  // cout << "i: " << i << ", j: " << j << ", n: " << n << endl;
  int ii = i, jj = j;
  while (lcs[ii - 1][jj] == n) ii--;
  while (lcs[ii][jj - 1] == n) jj--;

  trace(ii - 1, jj - 1, n - 1, s2);
  cout << s2[jj - 1];
}

int main() {
  fast_io();

  string s1, s2;
  cin >> s1 >> s2;
  int sz1 = s1.size(), sz2 = s2.size();

  for (int i = 1; i <= sz1; i++) {
    for (int j = 1; j <= sz2; j++) {
      if (s1[i - 1] == s2[j - 1]) lcs[i][j] = lcs[i - 1][j - 1] + 1;
      else lcs[i][j] = max(lcs[i][j - 1], lcs[i - 1][j]);
    }
  }

  // cout << "  ";
  // for (int j = 0; j < sz2; j++) cout << s2[j] << ' ';
  // cout  << endl;
  // for (int i = 0; i <= sz1; i++) {
  //   for (int j = 0; j <= sz2; j++) {
  //     cout << lcs[i][j] << ' ';
  //   }
  //   cout  << endl;
  // }

  int ans = lcs[sz1][sz2];
  cout << ans << '\n';

  if (ans) {
    trace(sz1, sz2, ans, s2);
    cout << '\n';
  }
}
