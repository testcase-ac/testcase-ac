#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int f(string t) {
  if (t == "A") return 11;
  if (t == "10" || t == "J" || t == "Q" || t == "K") return 10;
  return t[0] - '0';
}

int n, m;
void solve() {
  vector<int> A(n);
  for (int i = 0; i < n; ++i) {
    string t; cin >> t;
    A[i] = f(t);
  }
}

int main() {
  fast_io();

  while (cin >> n >> m) solve();
}
