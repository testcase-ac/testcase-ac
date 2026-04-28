#include <bits/stdc++.h>
using namespace std;

int ask(int k) {
  cout << "? " << k << endl;
  int z;
  cin >> z;
  return z;
}

void answer(int k) {
  cout << "! " << k << endl;
}

int main() {
  int n;
  cin >> n;

  int st = ask(1), et = ask(n);
  if (st < et) answer(1);
  if (st == et) answer(0);
  if (st > et) answer(-1);
}
