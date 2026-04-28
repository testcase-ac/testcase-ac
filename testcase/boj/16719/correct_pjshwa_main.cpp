#include <bits/stdc++.h>
using namespace std;

bool f[100];
void search_print(int sidx, int eidx, string& s) {
  char minc = 91;
  int mini = 101;
  bool found = false;

  for (int i = sidx; i <= eidx; i++) {
    if (!f[i] && minc > s[i]) {
      found = true;
      minc = s[i];
      mini = i;
    }
  }

  if (!found) return;
  f[mini] = true;

  int sz = s.size();
  for (int i = 0; i < sz; i++) {
    if (f[i]) cout << s[i];
  }
  cout << '\n';

  search_print(mini + 1, eidx, s);
  search_print(sidx, mini - 1, s);
}

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  string s;
  cin >> s;
  search_print(0, s.size() - 1, s);
}
