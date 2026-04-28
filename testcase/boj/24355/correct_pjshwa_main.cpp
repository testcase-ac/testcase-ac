#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int str[MAX + 10], plen[MAX + 10], N;

// find longest palindromic span for each element in str
// O(|str|)
void manacher() {
  int r = -1, p = -1;
  for (int i = 0; i < N; ++i) {
    if (i <= r) plen[i] = min((2 * p - i >= 0) ? plen[2 * p - i] : 0, r - i);
    else plen[i] = 0;

    while (
      i - plen[i] - 1 >= 0 && i + plen[i] + 1 < N &&
      str[i - plen[i] - 1] == str[i + plen[i] + 1]
    ) plen[i] += 1;

    if (i + plen[i] > r) {
      r = i + plen[i];
      p = i;
    }
  }
}

bool is_palindrome(int s, int e) {
  s = (s - 1) << 1;
  e = (e - 1) << 1;
  return e - (s + e) / 2 <= plen[(s + e) / 2];
}

void solve() {
  string S; cin >> S;
  int Z = S.size(); N = (Z << 1) - 1;

  for (int i = 0; i < N; i++) {
    if (i % 2) str[i] = -1;
    else str[i] = S[i / 2];
  }
  manacher();

  int maxlen = 0;
  for (int r = 1; r <= Z; ++r) {
    if (is_palindrome(1, r)) maxlen = r;
  }
  cout << 2 * Z - maxlen << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
