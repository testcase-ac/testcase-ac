#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

double cal(double a, double b, string op) {
  if (op == "+") return a + b;
  if (op == "-") return a - b;
  if (op == "*") return a * b;
  if (op == "/") return a / b;
  return 0;
}

void solve() {
  double O[3]; string op1, op2;
  cin >> O[0] >> op1 >> O[1] >> op2 >> O[2];

  double ans = cal(O[0], O[1], op1);
  ans = cal(ans, O[2], op2);

  cout << "=================\n";
  cout << "|SASA CALCULATOR|\n";

  // round to 3 decimal places
  stringstream ss;
  ss << fixed << setprecision(3) << ans;
  string s = ss.str();

  // pad spaces upto 15 characters
  cout << '|';
  cout << string(15 - s.size(), ' ') << s << "|\n";

  cout << "-----------------\n";
  cout << "|               |\n";
  cout << "| AC         /  |\n";
  cout << "| 7  8  9    *  |\n";
  cout << "| 4  5  6    -  |\n";
  cout << "| 1  2  3    +  |\n";
  cout << "|    0  .    =  |\n";
  cout << "=================\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
