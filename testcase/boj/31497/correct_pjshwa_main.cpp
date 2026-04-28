#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int ask(string s) {
  cout << "? " << s << endl;
  int ret; cin >> ret;
  return ret;
}

void solve() {
  int N; cin >> N;
  vector<string> A(N);
  for (auto& s : A) cin >> s;

  for (auto& s : A) {
    int sum = ask(s) + ask(s);
    if (sum > 0) {
      cout << "! " << s << endl;
      return;
    }
  }
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
