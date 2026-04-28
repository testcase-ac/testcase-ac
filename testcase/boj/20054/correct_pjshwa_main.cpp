#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int mod = 1e9 + 7;
ll d[3501][13];
ll tree_variety(int cnt, int hgt) {
  if (d[cnt][hgt] == -1) {
    ll ans = 0;
    for (int root = 0; root < cnt; root++) {
      ans = (ans + tree_variety(root, hgt - 1) * tree_variety(cnt - root - 1, hgt - 1)) % mod;
    }

    d[cnt][hgt] = ans;
  }

  return d[cnt][hgt];
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));
  for (int i = 0; i <= 12; i++) d[0][i] = 1;
  for (int i = 1; i <= 3500; i++) d[i][0] = 0;
  for (int i = 1; i <= 12; i++){
    int len = min((1 << i) - 1, 3500);
    for (int j = len + 1; j <= 3500; j++) d[j][i] = 0;
  }

  int n, k;
  cin >> n >> k;
  cout << tree_variety(n, k) << '\n';
}
