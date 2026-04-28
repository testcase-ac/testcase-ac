#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_vowel(char c) {
  return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void solve() {
  int N, M; string S; cin >> N >> M >> S;

  int state = 0; string ans = "";
  while (!S.empty()) {
    char c = S.back(); S.pop_back();
    if (state == 0) {
      if (!is_vowel(c)) state = 1, ans += c;
    }
    else if (state == 1) {
      if (c == 'A') state = 2, ans += c;
    }
    else if (state == 2) {
      if (c == 'A') state = 3, ans += c;
    }
    else if (state == 3) {
      ans += c;
      if (ans.size() == M) break;
    }
  }
  reverse(ans.begin(), ans.end());

  if (ans.size() == M && state == 3) cout << "YES" << '\n' << ans << '\n';
  else cout << "NO" << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
