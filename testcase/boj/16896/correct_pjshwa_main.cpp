#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool r(ll v) {
  if (v == 0) return true;
  if (v < 4) return false;

  ll pw4 = 1;
  while (pw4 * 4 <= v) pw4 *= 4;
  
  if (v / pw4 == 1) return r(v - pw4);
  else return false;
}

void solve() {
  ll N;
  cin >> N;

  if (r(2 * N - 2)) cout << "koosaga\n";
  else cout << "cubelover\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
