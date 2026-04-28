#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;
  int zc = 0, oc = 0, sz = s.size();

  for (int i = 0; i < sz; i++) {
    if (s[i] == '0') zc++;
    else oc++;
  }

  zc >>= 1;
  oc >>= 1;

  int i;
  i = sz - 1;
  while (zc) {
    if (s[i] == '0') {
      s[i] = '*';
      zc--;
    }
    i--;
  }

  i = 0;
  while (oc) {
    if (s[i] == '1') {
      s[i] = '*';
      oc--;
    }
    i++;
  }

  for (int i = 0; i < sz; i++) {
    if (s[i] != '*') cout << s[i];
  }
}
