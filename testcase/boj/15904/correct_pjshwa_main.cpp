#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  string s;
  getline(cin, s);

  int sz = s.size(), state = 0;
  char c;
  for (int i = 0; i < sz; i++) {
    c = s[i];
    if (state == 0 && c == 'U') state = 1;
    else if (state == 1 && c == 'C') state = 2;
    else if (state == 2 && c == 'P') state = 3;
    else if (state == 3 && c == 'C') state = 4;
  }

  cout << (state == 4 ? "I love UCPC" : "I hate UCPC") << '\n';
}
