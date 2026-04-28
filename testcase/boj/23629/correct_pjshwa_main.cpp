#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string expr;
  cin >> expr;
  int n = expr.size();

  stack<ll> s;
  char op = ' ';
  int i = 0;
  string cur = "", res = "";

  while (i < n) {
    if (expr[i] == '+' || expr[i] == '-' || expr[i] == 'x' || expr[i] == '/' || expr[i] == '=') {
      if (cur == "") cout << "Madness!\n", exit(0);

      if (op != ' ') res += op;
      res += cur;
      ll curi = stoll(cur), q;

      if (op == ' ') s.push(curi);
      if (op == '+') q = s.top(), s.pop(), s.push(q + curi);
      if (op == '-') q = s.top(), s.pop(), s.push(q - curi);
      if (op == 'x') q = s.top(), s.pop(), s.push(q * curi);
      if (op == '/') q = s.top(), s.pop(), s.push(q / curi);
      cur.clear();
      op = expr[i];
      i++;
    }
    else {
      if (expr.substr(i, 4) == "ZERO") cur += '0', i += 4;
      else if (expr.substr(i, 3) == "ONE") cur += '1', i += 3;
      else if (expr.substr(i, 3) == "TWO") cur += '2', i += 3;
      else if (expr.substr(i, 5) == "THREE") cur += '3', i += 5;
      else if (expr.substr(i, 4) == "FOUR") cur += '4', i += 4;
      else if (expr.substr(i, 4) == "FIVE") cur += '5', i += 4;
      else if (expr.substr(i, 3) == "SIX") cur += '6', i += 3;
      else if (expr.substr(i, 5) == "SEVEN") cur += '7', i += 5;
      else if (expr.substr(i, 5) == "EIGHT") cur += '8', i += 5;
      else if (expr.substr(i, 4) == "NINE") cur += '9', i += 4;
      else cout << "Madness!\n", exit(0);
    }
  }
  
  cout << res << "=\n";
  for (char e : to_string(s.top())) {
    if (e == '-') cout << '-';
    if (e == '0') cout << "ZERO";
    if (e == '1') cout << "ONE";
    if (e == '2') cout << "TWO";
    if (e == '3') cout << "THREE";
    if (e == '4') cout << "FOUR";
    if (e == '5') cout << "FIVE";
    if (e == '6') cout << "SIX";
    if (e == '7') cout << "SEVEN";
    if (e == '8') cout << "EIGHT";
    if (e == '9') cout << "NINE";
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
