#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  cout << "? " << (int)1e9 << endl;
  string ret;
  cin >> ret;

  cout << "! ";
  for (int i = 0; i <= N; i++) {
    int it = 9; string term = "";
    while (ret.size() && it--) {
      term += ret.back();
      ret.pop_back();
    }
    reverse(term.begin(), term.end());
    cout << stoi(term) << " ";
  }
  cout << endl;
}

int main() {
  // fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
