#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string s, cur = "";
set<string> vis;
int n;

void rec(int l, int r) {
  if (r - l + 1 == n) {
    vis.insert(cur);
    return;
  }

  if (l > 0) {
    for (int i = l - 1; i <= r; i++) cur += s[i];
    rec(l - 1, r);
    for (int i = l - 1; i <= r; i++) cur.pop_back();
  }
  if (r + 1 < s.size()) {
    for (int i = l; i <= r + 1; i++) cur += s[i];
    rec(l, r + 1);
    for (int i = l; i <= r + 1; i++) cur.pop_back();
  }
}

int main() {
  fast_io();

  cin >> s;
  n = s.size();
  for (int i = 0; i < n; i++) {
    cur += s[i];
    rec(i, i);
    cur.pop_back();
  }
  cout << vis.size() << '\n';
}
