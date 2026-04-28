#include <bits/stdc++.h>
using namespace std;

int ask(int x) {
  cout << x << endl;
  int ret;
  cin >> ret;
  return ret;
}

void say(int x) {
  cout << x << endl;
}

void winning_loop(int s) {
  if (s == 99) {
    say(s);
    return;
  }

  // r is always NOT a multiple of 3
  int r = ask(s);
  winning_loop(r + 3 - (r % 3));
}

int main() {
  int r = ask(1);
  if (r % 3) winning_loop(r + 3 - (r % 3));
  else {
    while (r % 3 == 0) r = ask(r + 2);
    winning_loop(r + 3 - (r % 3));
  }
}
