#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S(int i) {
  if (i <= 2) return "()";
  return "(" + S(i - 2) + S(i - 1) + ")";
}

void solve() {
  ll n, k; cin >> n >> k;

  string s = S(n);
  if (k > s.size()) cout << "0\n";
  else cout << s[k - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
