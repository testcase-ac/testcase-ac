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

  bool c13 = false, c14 = false, c34 = false;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    if (a == 2 || a == 5 || b == 2 || b == 5) {
      cout << "Woof-meow-tweet-squeek\n";
      return 0;
    }

    if (a == 1 && b == 3) c13 = true;
    if (a == 3 && b == 1) c13 = true;
    if (a == 1 && b == 4) c14 = true;
    if (a == 4 && b == 1) c14 = true;
    if (a == 4 && b == 3) c34 = true;
    if (a == 3 && b == 4) c34 = true;
  }

  if (c13 && c14 && c34) cout << "Wa-pa-pa-pa-pa-pa-pow!\n";
  else cout << "Woof-meow-tweet-squeek\n";
}
