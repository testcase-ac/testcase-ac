#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

tuple<int, int, int> ans[500000];
int main() {
  fast_io();

  int n, k, l, x1, x2, x3, cnt = 0;
  cin >> n >> k >> l;
  for (int i = 0; i < n; i++) {
    cin >> x1 >> x2 >> x3;
    if (x1 >= l && x2 >= l && x3 >= l && x1 + x2 + x3 >= k) ans[cnt++] = {x1, x2, x3};
  }

  cout << cnt << '\n';
  for (int i = 0; i < cnt; i++) {
    tie(x1, x2, x3) = ans[i];
    cout << x1 << ' ' << x2 << ' ' << x3 << ' ';
  }
  cout << '\n';
}
