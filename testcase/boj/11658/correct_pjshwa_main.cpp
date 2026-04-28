#include <bits/stdc++.h>
using namespace std;

const int MAX = 1 << 11;
int P[MAX + 1][MAX + 1], n;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int query(int x, int y) {
  int ret = 0;
  for(int i=x; i>0; i -= (i&-i)){
    for(int j=y; j>0; j -= (j&-j)){
      ret += P[i][j];
    }
  }
  return ret;
}

int sum(int x1, int y1, int x2, int y2) {
  return query(x2, y2) - query(x2, y1-1) - query(x1-1, y2) + query(x1-1, y1-1);
}

void update(int x, int y, int val) {
  for(int i=x; i<=n; i += (i&-i)){
    for(int j=y; j<=n; j += (j&-j)){
      P[i][j] += val;
    }
  }
}

int main() {
  fast_io();

  int x, m;
  cin >> n >> m;
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> x, update(i, j, x);

  while (m--) {
    int w, a, b, c, d;
    cin >> w >> a >> b >> c;

    if (w == 0) update(a, b, c - sum(a, b, a, b));
    else {
      cin >> d;
      cout << sum(a, b, c, d) << '\n';
    }
  }
}
