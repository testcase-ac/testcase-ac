#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string S;
void solve() {
  for (int i = 0; i < 128; i++) {
    if (S[i] != S[i ^ 8]) return cout << "no\n", void();
  }
  cout << "yes\n";
}

int main() {
  fast_io();

  while (1) {
    cin >> S;
    if (S == "#") break;
    solve();
  }
}
