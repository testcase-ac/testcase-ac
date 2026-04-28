#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll N;
map<ll, bool> d;
bool r(ll n) {
  if (d.count(n)) return d[n];
  if (n >= N) return d[n] = false;

  bool ret = false;
  for (int i = 2; i <= 9; ++i) ret |= !r(n * i);
  return d[n] = ret;
}

void solve() {
  d.clear();

  if (r(1)) cout << "Baekjoon wins.\n";
  else cout << "Donghyuk wins.\n";
}

int main() {
  fast_io();
 
  while (cin >> N) solve();
}
