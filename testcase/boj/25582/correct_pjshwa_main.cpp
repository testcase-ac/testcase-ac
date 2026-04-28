#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool point_refl(int a, int b) {
  if (a == -1 && b == -1) return true;
  if (a == 'p' && b == 'd') return true;
  if (a == 'd' && b == 'p') return true;
  if (a == 'b' && b == 'q') return true;
  if (a == 'q' && b == 'b') return true;
  if (a == 'u' && b == 'n') return true;
  if (a == 'n' && b == 'u') return true;
  if (a == 's' && b == 's') return true;
  if (a == 'z' && b == 'z') return true;
  if (a == 'l' && b == 'l') return true;
  if (a == 'o' && b == 'o') return true;
  if (a == 'x' && b == 'x') return true;
  return false;
}

bool window_refl(int a, int b) {
  if (a == -1 && b == -1) return true;
  if (a == 'p' && b == 'q') return true;
  if (a == 'q' && b == 'p') return true;
  if (a == 'b' && b == 'd') return true;
  if (a == 'd' && b == 'b') return true;
  if (a == 'i' && b == 'i') return true;
  if (a == 'm' && b == 'm') return true;
  if (a == 'v' && b == 'v') return true;
  if (a == 'w' && b == 'w') return true;
  if (a == 'l' && b == 'l') return true;
  if (a == 'o' && b == 'o') return true;
  if (a == 'x' && b == 'x') return true;
  return false;
}

class StringWPW {
  vector<int> str, plen;
  int n;

  void manacher() {
    int r = -1, p = -1;
    for (int i = 0; i < n; ++i) {
      if (i <= r) plen[i] = min((2 * p - i >= 0) ? plen[2 * p - i] : 0, r - i);
      else plen[i] = 0;

      while (
        i - plen[i] - 1 >= 0 && i + plen[i] + 1 < n &&
        window_refl(str[i - plen[i] - 1], str[i + plen[i] + 1])
      ) plen[i] += 1;

      if (i + plen[i] > r) {
        r = i + plen[i];
        p = i;
      }
    }
  }

public:
  StringWPW(string& s) {
    n = (s.size() << 1) + 1;
    str.resize(n);
    plen.resize(n);

    for (int i = 0; i < n; i++) {
      if (i % 2) str[i] = s[i / 2];
      else str[i] = -1;
    }

    manacher();
  }

  StringWPW(vector<int>& s) {
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

  int max_length() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (!window_refl(str[i], str[i])) continue;
      ans = max(ans, plen[i]);
    }
    return ans;
  }
};


class StringWPP {
  vector<int> str, plen;
  int n;

  void manacher() {
    int r = -1, p = -1;
    for (int i = 0; i < n; ++i) {
      if (i <= r) plen[i] = min((2 * p - i >= 0) ? plen[2 * p - i] : 0, r - i);
      else plen[i] = 0;

      while (
        i - plen[i] - 1 >= 0 && i + plen[i] + 1 < n &&
        point_refl(str[i - plen[i] - 1], str[i + plen[i] + 1])
      ) plen[i] += 1;

      if (i + plen[i] > r) {
        r = i + plen[i];
        p = i;
      }
    }
  }

public:
  StringWPP(string& s) {
    n = (s.size() << 1) + 1;
    str.resize(n);
    plen.resize(n);

    for (int i = 0; i < n; i++) {
      if (i % 2) str[i] = s[i / 2];
      else str[i] = -1;
    }

    manacher();
  }

  StringWPP(vector<int>& s) {
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

  int max_length() {
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (!point_refl(str[i], str[i])) continue;
      ans = max(ans, plen[i]);
    }
    return ans;
  }
};

void solve() {
  string S;
  cin >> S;

  StringWPW wpw(S);
  StringWPP wpp(S);

  int ans = max(wpw.max_length(), wpp.max_length());
  if (ans == 0) cout << "NOANSWER\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
