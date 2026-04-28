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

  for (int i = 0; i < s.size(); i++) {
    int ascii_val = s[i];
    int rep = 0;
    while (ascii_val) {
      rep += ascii_val % 10;
      ascii_val /= 10;
    }
    for (int j = 0; j < rep; j++) cout << s[i];
    cout << '\n';
  }
}
