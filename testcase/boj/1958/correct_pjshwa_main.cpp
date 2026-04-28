#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
int d[MAX + 1][MAX + 1][MAX + 1];

void solve() {
  string s1, s2, s3;
  cin >> s1 >> s2 >> s3;
  int sz1 = s1.size(), sz2 = s2.size(), sz3 = s3.size();

  for (int i = 1; i <= sz1; i++) for (int j = 1; j <= sz2; j++) for (int k = 1; k <= sz3; k++) {
    if (s1[i - 1] == s2[j - 1] && s2[j - 1] == s3[k - 1]) {
      d[i][j][k] = d[i - 1][j - 1][k - 1] + 1;
    }
    d[i][j][k] = max({d[i][j][k], d[i][j][k - 1], d[i][j - 1][k], d[i - 1][j][k]});
  }

  cout << d[sz1][sz2][sz3] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
