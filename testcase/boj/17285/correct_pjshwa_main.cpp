#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  string s;
  cin >> s;
  int k = s[0] ^ 'C';
  for (auto &ch : s) cout << (char)(ch ^ k);
}
