#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string u;

void rec(int l, int r) {
  if (l == r) return;

  int diff = (r - l + 1) / 3;
  for (int i = l + diff; i <= r - diff; i++) u[i] = ' ';
  rec(l, l + diff - 1);
  rec(r - diff + 1, r);
}

void solve(int n) {
  int pw = 1;
  for (int i = 0; i < n; i++) pw *= 3;

  u.resize(pw, '-');
  rec(0, pw - 1);

  cout << u << '\n';
}

int main() {
  fast_io();

  int n;
  while (cin >> n) solve(n);
}
