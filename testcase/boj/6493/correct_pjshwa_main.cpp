#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool is_slump(string s) {
  int n = s.size();
  if (n < 2) return false;
  if (!(s[0] == 'D' || s[0] == 'E')) return false;

  int i = 1;
  while (i < n && s[i] == 'F') i++;
  if (i == n || i == 1) return false;

  if (i == n - 1 && s[i] == 'G') return true;
  else return is_slump(s.substr(i));
}

bool is_slimp(string s) {
  int n = s.size();
  if (n < 2) return false;
  if (s == "AH") return true;
  if (s[n - 1] != 'C') return false;

  if (s.substr(0, 2) == "AB") return is_slimp(s.substr(2, n - 3));
  else if (s.substr(0, 1) == "A") return is_slump(s.substr(1, n - 2));
  else return false;
}

bool is_slurpy(string s) {
  int n = s.size();
  for (int i = 1; i < n; i++) {
    if (is_slimp(s.substr(0, i)) && is_slump(s.substr(i))) return true;
  }
  return false;
}

void solve() {
  string s;
  cin >> s;
  cout << (is_slurpy(s) ? "YES" : "NO") << '\n';
}

int main() {
  fast_io();

  // cout << "SLURPYS OUTPUT\n";

  int t;
  cin >> t;
  while (t--) solve();

  // cout << "END OF OUTPUT\n";
}
