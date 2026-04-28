#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool s[1001];
int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  int cnt = 0;
  s[0] = s[1] = true;
  for (int i = 2; i <= n; i++) {
    if (s[i]) continue;

    if (++cnt == k) {
      cout << i << '\n';
      return 0;
    }

    for (int j = 2 * i; j <= n; j += i) {
      if (s[j]) continue;

      s[j] = true;
      if (++cnt == k) {
        cout << j << '\n';
        return 0;
      }
    }
  }
}
