#include <bits/stdc++.h>
using namespace std;

int ask(char o, int x) {
  cout << "? " << o << ' ' << x << endl;
  int ret;
  cin >> ret;
  return ret;
}

void answer(int x) {
  cout << "! " << x << endl;
}

int main() {
  int n;
  cin >> n;

  int al = 1, ah = n, bl = 1, bh = n;
  for (int i = 0; i < 20; i++) {
    if (al == ah && bl == bh) {
      answer(min(ask('A', al), ask('B', bl)));
      break;
    }
    int am = (al + ah) / 2;
    int bm = (bl + bh) / 2;
    int av = ask('A', am), bv = ask('B', bm);
    if (av >= bv) {
      ah = am;
      bl = bm + 1;
    }
    else {
      al = am + 1;
      bh = bm;
    }
  }
}
