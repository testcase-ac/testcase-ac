#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S;
void solve() {
  int N = stoi(S), csum = 0;
  for (char ch : S) {
    if (ch == '-') continue;
    csum += ch - '0';
  }

  for (int c = N - 1;; --c) {
    int dsum = 0;
    for (char ch : to_string(c)) {
      if (ch == '-') continue;
      dsum += ch - '0';
    }
    if (dsum == csum + 1) {
      cout << c << '\n';
      return;
    }
  }
}

int main() {
  fast_io();

  while (cin >> S) {
    if (S == "END") break;
    solve();
  }
}
