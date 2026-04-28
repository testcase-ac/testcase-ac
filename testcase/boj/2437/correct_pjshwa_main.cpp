#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[1001], s[1001];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  sort(a, a + n);
  s[0] = a[0];
  for (int i = 1; i < n; i++) s[i] = s[i - 1] + a[i];
  a[n] = 2e9;

  if (a[0] > 1) {
    cout << 1;
    return 0;
  }

  for (int i = 1; i <= n; i++) {
    if (a[i] > s[i - 1] + 1) {
      cout << s[i - 1] + 1;
      break;
    }
  }

}
