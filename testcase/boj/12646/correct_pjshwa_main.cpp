#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve(int tc) {
  string s;
  cin >> s;

  char sc[25];
  memset(sc, 0, sizeof sc);
  for (int i = 0; i < s.size(); i++) sc[i] = s[i];

  cout << "Case #" << tc << ": ";

  if (next_permutation(sc, sc + s.size())) cout << sc << '\n';
  else {
    sort(sc, sc + s.size());
    int first_nonzero = 0;
    while (sc[first_nonzero] == '0') first_nonzero++;
    cout << sc[first_nonzero] << 0;
    for (int i = 0; i < first_nonzero; i++) cout << sc[i];
    for (int i = first_nonzero + 1; i < s.size(); i++) cout << sc[i];
    cout << '\n';
  }
}

int main() {
  fast_io();
  
  int t;
  cin >> t;
  for (int i = 1; i <= t; i++) solve(i);
}
