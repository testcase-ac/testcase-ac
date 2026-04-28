#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool dir[10];
int mp[10], xp[10], p[10];

bool pless(int* p, int* c) {
  for (int i = 0; i < 10; i++) {
    if (p[i] < c[i]) return true;
    if (p[i] > c[i]) return false;
  }
  return false;
}

void passign(int* t, int* p) {
  for (int i = 0; i < 10; i++) t[i] = p[i];
}

void solve() {
  int n;
  string s;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> s;
    dir[i] = s == "<";
  }

  for (int i = 0; i < 10; i++) {
    p[i] = xp[i] = i;
    mp[i] = 9 - i;
  }

  do {
    bool able = true;
    for (int i = 0; i < n; i++) {
      if (p[i] < p[i + 1] && !dir[i]) able = false;
      if (p[i] > p[i + 1] && dir[i]) able = false;
    }
    if (!able) continue;

    if (pless(p, mp)) passign(mp, p);
    if (pless(xp, p)) passign(xp, p);

  } while (next_permutation(p, p + 10));

  for (int i = 0; i <= n; i++) cout << xp[i];
  cout << '\n';
  for (int i = 0; i <= n; i++) cout << mp[i];
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
