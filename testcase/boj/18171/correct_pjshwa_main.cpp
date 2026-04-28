#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int str[MAX + 1], plen[MAX + 1];
int N;

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
  string S;
  cin >> N >> S;

  int ON = N;
  N = (N << 1) - 1;

  for (int i = 0; i < N; i++) {
    if (i % 2) str[i] = -1;
    else str[i] = S[i / 2];
  }

  memset(plen, 0, sizeof plen);
  manacher();

  int ans = ON - 1;
  for (int i = ON - 1; i >= 1; i--) {
    if (is_palindrome(i, ON)) ans = min(ans, i - 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
