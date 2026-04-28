#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int cnt[10];
int main() {
  fast_io();

  int n, a, b;
  bool able;
  cin >> n;
  for (int i = 1; i < 1e5; i++) {
    able = true;
    a = i, b = n - i;
    if (b <= 0) break;

    memset(cnt, 0, sizeof(cnt));
    while (a) cnt[a % 10]++, a /= 10;
    while (b) cnt[b % 10]++, b /= 10;
    for (int j = 0; j < 10; j++) if (cnt[j] > 1) able = false;
    if (able) {
      cout << i << " + " << n - i;
      return 0;
    }
  }

  cout << -1;
}
