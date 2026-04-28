#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_operator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/';
}

void solve() {
  string S; cin >> S;

  ll A = 0, B = 0, As = 1, Bs = 1;
  int i = 0, N = S.size();
  if (S[i] == '-') {
    i++;
    As = -1;
  }

  for (; i < N; i++) {
    if (is_operator(S[i])) break;
    A = A * 8 + S[i] - '0';
  }
  char op = S[i++];
  if (S[i] == '-') {
    i++;
    Bs = -1;
  }

  for (; i < N; i++) {
    B = B * 8 + S[i] - '0';
  }

  ll ans_10;
  if (op == '+') ans_10 = As * A + Bs * B;
  else if (op == '-') ans_10 = As * A - Bs * B;
  else if (op == '*') ans_10 = As * A * Bs * B;
  else {
    if (B == 0) return cout << "invalid\n", void();

    if (As * Bs == -1) ans_10 = (A - 1) / B + 1;
    else ans_10 = A / B;
    ans_10 = As * Bs * ans_10;
  }

  int sign = 1;
  if (ans_10 < 0) sign *= -1, ans_10 *= -1;

  string ans_8;
  while (ans_10) {
    ans_8 += ans_10 % 8 + '0';
    ans_10 /= 8;
  }
  reverse(ans_8.begin(), ans_8.end());

  if (ans_8.empty()) cout << "0\n";
  else {
    if (sign == -1) cout << '-';
    cout << ans_8 << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
