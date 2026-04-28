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

  int ml = 0, mv = 0, tmp, a, b;
  for (int i = 0; i <= n; i++) {
    a = n, b = i;
    int cl = 2;
    while (b >= 0) {
      tmp = b;
      b = a - b;
      a = tmp;
      cl++;
    }

    if (ml < cl) {
      mv = i;
      ml = cl;
    }
  }

  cout << ml - 1 << '\n';

  a = n, b = mv;
  cout << a << ' ';
  while (b >= 0) {
    cout << b << ' ';
    tmp = b;
    b = a - b;
    a = tmp;
  }
  cout << '\n';
}
