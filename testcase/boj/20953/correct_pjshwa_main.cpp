#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, a, b;
  cin >> n;

  while (n--) {
    cin >> a >> b;
    cout << (a + b) * (a + b - 1) / 2 * (a + b) << '\n';
  }
}
