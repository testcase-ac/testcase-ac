#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 10000;
int d[MAX + 1];
int N;

bool r(int v) {
  if (d[v] != -1) return d[v];

  bool ret = false;
  if (v + 1 < N) ret |= !r(v + 1);
  if (2 * v < N) ret |= !r(2 * v);

  return d[v] = ret;
}

void solve() {
  cin >> N;

  memset(d, -1, sizeof(d));
  if (r(1)) cout << "koosaga\n";
  else cout << "cubelover\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
