#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n;
  cin >> n;

  string s;
  char c;
  cin >> s;
  c = s[0];

  n--;
  while (n--) {
    cin >> s;
    if (s[0] != c) {
      cout << "0\n";
      return 0;
    }
  }

  cout << "1\n";
}
