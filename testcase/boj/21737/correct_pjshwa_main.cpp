#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool is_operator(char c) {
  return c == 'S' || c == 'M' || c == 'U' || c == 'P' || c == 'C';
}

int cal(int arg1, int arg2, char op) {
  if (!op) return arg1;
  if (op == 'S') return arg1 - arg2;
  if (op == 'M') return arg1 * arg2;
  if (op == 'U') return arg1 / arg2;
  if (op == 'P') return arg1 + arg2;
}

void solve() {
  int n;
  string s;
  cin >> n >> s;

  int arg1 = 0, arg2 = 0;
  char op = 0;

  bool output = 0;
  for (int i = 0; i < s.size(); i++) {
    if (is_operator(s[i])) {
      arg1 = cal(arg1, arg2, op), arg2 = 0;
      if (s[i] == 'C') cout << arg1 << ' ', op = 0, output = 1;
      else op = s[i];
    }
    else {
      if (op) arg2 = 10 * arg2 + (s[i] - '0');
      else arg1 = 10 * arg1 + (s[i] - '0');
    }
  }

  if (output) cout << '\n';
  else cout << "NO OUTPUT\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
