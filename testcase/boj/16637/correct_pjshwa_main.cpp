#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, mv = 1 << 31;
string s;

int cal(int a, int b, char op) {
  int result = a;
  if (op == '+') return a + b;
  if (op == '-') return a - b;
  if (op == '*') return a * b;
}

void r(int idx, int cv) {
  if (idx > n - 1) mv = max(mv, cv);
  else {
    char op = (idx == 0) ? '+' : s[idx - 1];

    if (idx + 2 < n) r(idx + 4, cal(cv, cal(s[idx] - '0', s[idx + 2] - '0', s[idx + 1]), op));
    r(idx + 2, cal(cv, s[idx] - '0', op));
  }
}

int main() {
  fast_io();

  cin >> n >> s;
  r(0, 0);
  cout << mv;
}
