#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int a[(int)1e3 + 1];
int main() {
  fast_io();

  int n;
  cin >> n;

  a[0] = 1;
  a[1] = 1;

  for (int i = 2; i <= 1000; i++) {
    int j = 1;
    while (1) {
      bool able = true;
      for (int k = 1; i - 2 * k >= 0; k++) {
        if (j + a[i - 2 * k] == 2 * a[i - k]) able = false;
      }
      if (able) {
        a[i] = j;
        break;
      }
      else j++;
    }
  }
  cout << a[n] << '\n';
}
