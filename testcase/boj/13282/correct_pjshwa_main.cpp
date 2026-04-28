#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 7368791;
bitset<MAX + 1> a;

int main() {
  fast_io();

  while (1) {
    int m, n;
    cin >> m >> n;
    if (n == 0 && m == 0) break;

    a.reset();
    int c = m;
    while (1) {
      if (!a[c]) {
        if (!n) break;
        n--;
        for (int j = c; j <= MAX; j += c) a[j] = 1;
      }
      c++;
    }
    cout << c << '\n';
  }
}
