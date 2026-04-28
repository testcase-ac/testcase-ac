#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int k;
  string s;
  cin >> k >> s;
  for (int i = 0; i < s.size(); i += k) cout << s[i];
}
