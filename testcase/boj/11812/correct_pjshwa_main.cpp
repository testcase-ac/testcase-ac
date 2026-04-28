#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll n, x, y, cnt;
  int k, q;
  cin >> n >> k >> q;

  while (q--) {
    cin >> x >> y;

    if (k == 1) cnt = abs(x - y);
    else {
      cnt = 0;
      while (x != y) {
        if (x < y) y = (y - 2) / k + 1;
        else x = (x - 2) / k + 1;
        cnt++;
      }
    }
    cout << cnt << '\n';
  }
}
