#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_digit(char c) {
  return '0' <= c && c <= '9';
}

pii parse(string O) {
  int an = 0, bn = 0;

  reverse(O.begin(), O.end());
  O.pop_back();
  while (is_digit(O.back())) {
    an = an * 10 + O.back() - '0';
    O.pop_back();
  }
  O.pop_back();
  while (is_digit(O.back())) {
    bn = bn * 10 + O.back() - '0';
    O.pop_back();
  }

  return {an, bn};
}

string problem_id;
void solve() {
  int m, n, p;
  cin >> m >> n >> p;

  while (p--) {
    string A, B;
    cin >> A >> B;
    cout << "ProblemID " << problem_id << ": " << A << " * " << B << " = ";

    pii a = parse(A), b = parse(B);
    int u = 1, r1 = 0, r2 = (a.second + b.second) % n;
    for (int i = 0; i < a.second; i++) u = (u * (m - 1)) % m;
    for (int i = 0; i < b.first; i++) r1 = (r1 + u) % m;
    r1 = (r1 + a.first) % m;

    cout << 'a' << r1 << 'b' << r2 << '\n';
  }
}

int main() {
  fast_io();

  while (1) {
    cin >> problem_id;
    if (problem_id == "ZZ") break;
    solve();
  }
}
