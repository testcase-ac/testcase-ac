#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
char ans[20][MAX];
int lg;

void r(int d, int s, int e) {
  if (d == lg) return;
  if (s + 1 == e) return;

  int m = (s + e) / 2;
  for (int i = s; i < m; i++) ans[d][i] = 'A';
  for (int i = m; i < e; i++) ans[d][i] = 'B';
  r(d + 1, s, m);
  r(d + 1, m, e);
}

void solve() {
  int n;
  cin >> n;

  if (n == 3) {
    cout << "2\n2 1 3\n2 1 2\n";
    return;
  }

  int flag;
  for (flag = 1; flag < n; flag <<= 1);
  lg = log2(flag);

  for (int i = 0; i < lg; i++) {
    for (int j = 0; j < n - 1; j++) ans[i][j] = 'A';
    ans[i][n - 1] = 'B';
  }

  r(0, 0, n);
  cout << lg << '\n';
  for (int i = 0; i < lg; i++) {
    vector<int> res;
    for (int j = 0; j < n; j++) if (ans[i][j] == 'A') res.push_back(j + 1);

    cout << res.size() << ' ';
    for (int e : res) cout << e << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
