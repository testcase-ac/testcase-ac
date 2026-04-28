#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5;
bool e[MAX + 1];

int main() {
  int n, x;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> x, e[x] = true;

  vector<int> ec, bc;
  for (int i = 1; i <= 2 * n; i++) {
    if (e[i]) ec.push_back(i);
    else bc.push_back(i);
  }

  int bp = 0, ans = 0;
  for (int c : ec) {
    while (bp < n && bc[bp] < c) bp++;
    if (bp == n) break;
    bp++;
    ans++;
  }
  cout << ans << '\n';
}
