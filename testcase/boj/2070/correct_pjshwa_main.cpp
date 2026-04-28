#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S;
bool is_necklace(int l, int z) {
  string sub = S.substr(l, z);

  // for all rotations of sub
  for (int i = 0; i < z; ++i) {
    string rotated = sub.substr(i) + sub.substr(0, i);
    if (rotated < sub) return false;
  }
  return true;
}

void solve() {
  cin >> S;
  int N = S.size();

  int l = 0;
  while (l < N) {
    int r = N;
    while (!is_necklace(l, r - l)) --r;
    cout << '(' << S.substr(l, r - l) << ')';
    l = r;
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
