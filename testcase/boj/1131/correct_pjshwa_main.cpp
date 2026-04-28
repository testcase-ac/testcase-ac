#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int sk(int n, int k) {
  int res = 0;
  while (n) {
    int ni = n % 10, a = 1;
    for (int i = 0; i < k; i++) a *= ni;
    res += a;
    n /= 10;
  }
  return res;
}

const int MAX = 4e6;
int d[MAX], c[MAX], k;

int dfs(int n) {
  d[n] = n;
  c[n]++;
  int x = sk(n, k);
  if (c[x] <= 1) return d[n] = min(d[n], dfs(x));
  else return d[n] = min(d[n], d[x]);
}

int main() {
  fast_io();

  int a, b;
  cin >> a >> b >> k;
  memset(d, -1, sizeof(d));

  for (int i = 1; i <= 1e6; i++) {
    if (d[i] == -1) dfs(i);
  }
  long long ans = 0;
  for (int i = a; i <= b; i++) ans += d[i];
  cout << ans;
}
