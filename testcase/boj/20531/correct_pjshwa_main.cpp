#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MOD = 1e9 + 7;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll d[5001][5001];
int parent[5001];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

int main() {
  fast_io();

  for (int i = 1; i <= 5000; i++) d[i][1] = 1;
  for (int i = 2; i <= 5000; i++) {
    for (int j = 2; j <= i; j++) d[i][j] = (d[i - 1][j] * j + d[i - 1][j - 1]) % MOD;
  }
  for (int i = 2; i <= 5000; i++) for (int j = 2; j <= i; j++) d[i][j] = (d[i][j] + d[i][j - 1]) % MOD;

  int n, m, a, b;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) parent[i] = i;

  while (m--) {
    cin >> a >> b;
    if (Find(a) != Find(b)) {
      Union(a, b);
      n--;
    }

    cout << d[n][n] << '\n';
  }
}
