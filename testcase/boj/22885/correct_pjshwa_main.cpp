#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[100];
int main() {
  fast_io();

  int t, n;
  cin >> t;

  for (int tc = 1; tc <= t; tc++) {
    cin >> n;

    for (int i = 0; i < n; i++) cin >> a[i];

    int cost = 0;
    for (int i = 0; i < n - 1; i++) {
      int j = min_element(a + i, a + n) - a;
      cost += (j - i + 1);
      reverse(a + i, a + j + 1);
    }

    cout << "Case #" << tc << ": " << cost << '\n';
  }

}
