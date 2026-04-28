#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e4 + 10, INF = 1e9 + 7;
bool add[MAX];
int a[MAX], d[MAX];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++) {
    cin >> a[i];
    add[a[i]] = true;
  }

  for (int i = 0; i < m; i++) for (int j = i + 1; j < m; j++) add[a[i] + a[j]] = true;

  for (int ni = 1; ni <= n; ni++) d[ni] = INF;
  d[0] = 0;
  for (int ni = 1; ni <= n; ni++) {
    for (int nj = ni; nj <= n; nj++) {
      if (add[ni]) d[nj] = min(d[nj], d[nj - ni] + 1);
    }
  }

  cout << (d[n] == INF ? -1 : d[n]) << '\n';
}
