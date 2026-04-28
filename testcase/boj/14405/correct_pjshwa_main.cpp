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

  int sz = s.size(), state = 0;
  char c;
  for (int i = 0; i < sz; i++) {
    c = s[i];
    if (state == 0 && c == 'p') state = 1;
    else if (state == 1 && c == 'i') state = 0;
    else if (state == 0 && c == 'k') state = 2;
    else if (state == 2 && c == 'a') state = 0;
    else if (state == 0 && c == 'c') state = 3;
    else if (state == 3 && c == 'h') state = 4;
    else if (state == 4 && c == 'u') state = 0;
    else state = 5;

    if (state == 5) break;
  }

  cout << (state == 0 ? "YES" : "NO") << '\n';
}
