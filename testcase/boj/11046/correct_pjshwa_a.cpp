#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

class StringWP {
  vector<int> str, plen;
  int n;

  void manacher() {
    int r = -1, p = -1;
    for (int i = 0; i < n; ++i) {
      if (i <= r) plen[i] = min((2 * p - i >= 0) ? plen[2 * p - i] : 0, r - i);
      else plen[i] = 0;

      while (
        i - plen[i] - 1 >= 0 && i + plen[i] + 1 < n &&
        str[i - plen[i] - 1] == str[i + plen[i] + 1]
      ) plen[i] += 1;

      if (i + plen[i] > r) {
        r = i + plen[i];
        p = i;
      }
    }
  }

public:
  StringWP(string& s) {
    n = (s.size() << 1) + 1;
    str.resize(n);
    plen.resize(n);

    for (int i = 0; i < n; i++) {
      if (i % 2) str[i] = -1;
      else str[i] = s[i / 2];
    }

    manacher();
  }

  StringWP(vector<int>& s) {
    n = (s.size() << 1) + 1;
    str.resize(n);
    plen.resize(n);

    for (int i = 0; i < n; i++) {
      if (i % 2) str[i] = -1;
      else str[i] = s[i / 2];
    }

    manacher();
  }

  bool is_palindrome(int s, int e) {
    s = (s - 1) << 1;
    e = (e - 1) << 1;
    return e - (s + e) / 2 <= plen[(s + e) / 2];
  }

};

void solve() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  StringWP swp(A);
  int Q;
  cin >> Q;
  while (Q--) {
    int s, e;
    cin >> s >> e;
    cout << swp.is_palindrome(s, e) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
