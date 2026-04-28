#include <bits/stdc++.h>
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int shoots[100000];
int main() {
  FastIO();

  int m, n, l, x, y, x_dist, cnt = 0;
  int* lbp;
  cin >> m >> n >> l;

  for (int i = 0; i < m; i++) cin >> shoots[i];
  sort(shoots, shoots + m);

  while (n--) {
    cin >> x >> y;
    lbp = lower_bound(shoots, shoots + m, x);
    if (lbp == shoots + m) x_dist = x - shoots[m - 1];
    else if (lbp == shoots) x_dist = shoots[0] - x;
    else x_dist = min(*lbp - x, x - *(lbp - 1));

    if (l >= x_dist + y) cnt++;
  }

  cout << cnt << '\n';
}
