#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();
  string op;

  int qs = 0;
  while (1) {
    getline(cin, op);
    if (op == "고무오리 디버깅 끝") break;

    if (op == "문제") qs++;
    else if (op == "고무오리") {
      if (qs) qs--;
      else qs = 2;
    }
  }

  cout << (qs ? "힝구" : "고무오리야 사랑해") << '\n';
}
