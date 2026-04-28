#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void solve() {
  int Y, M;
  cin >> Y >> M;

  if (M == 1) Y--, M = 12;
  else M--;

  bool lunar = Y % 4 == 0 && (Y % 100 != 0 || Y % 400 == 0);
  int D = months[M];
  if (lunar && M == 2) D++;

  cout << Y << ' ' << M << ' ' << D << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
