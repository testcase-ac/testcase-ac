#include <bits/stdc++.h> 
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  string s;
  cin >> s;
  int sz = s.size();

  int lkc = 0, rkc = 0;
  for (int i = 0; i < sz; i++) rkc += (s[i] == 'K');

  vector<int> rl, rr;

  for (int i = 0; i < sz; i++) {
    if (s[i] == 'R') {
      rl.push_back(lkc);
      rr.push_back(rkc);
    }
    else {
      lkc++;
      rkc--;
    }
  }

  int lp = 0, rp = rl.size() - 1, mv = 0;
  while (lp <= rp) {
    mv = max(mv, rp - lp + 1 + 2 * min(rl[lp], rr[rp]));
    if (rl[lp] < rr[rp]) lp++;
    else rp--;
  }
  cout << mv;
}
