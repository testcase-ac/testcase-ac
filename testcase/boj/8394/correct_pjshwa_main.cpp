#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  if (n == 1) cout << 1;
  else {
    int f1 = 1, f2 = 2, tmp;
    n -= 2;
    while (n--) {
      tmp = f1;
      f1 = f2;
      f2 = f2 + tmp;
      if (f2 >= 10) f2 -= 10;
    }
    cout << f2;
  }
}
