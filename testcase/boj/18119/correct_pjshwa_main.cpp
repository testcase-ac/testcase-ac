#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1 << 21;

bool is_vowel(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int bit(char c) {
  int o = 0;
  for (char u = 'a'; u <= 'z'; u++) {
    if (u == c) return o;

    if (is_vowel(u)) continue;
    o++;
  }
  return o;
}

void solve() {
  int N, M;
  cin >> N >> M;

  vector<int> W;
  for (int i = 0; i < N; i++) {
    string S; cin >> S;

    int mask = 0;
    for (char& c : S) {
      if (is_vowel(c)) continue;
      mask |= 1 << bit(c);
    }
    W.push_back(mask);
  }

  int mask = MAX - 1;
  while (M--) {
    int op; string c; cin >> op >> c;
    mask ^= 1 << bit(c[0]);

    int cnt = 0;
    for (int m : W) {
      if ((m & mask) == m) cnt++;
    }
    cout << cnt << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
