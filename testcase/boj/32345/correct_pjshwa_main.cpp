#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e9 + 7;

bool is_vowel(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  deque<int> dq; int streak = 0;
  for (int i = 0; i < N; ++i) {
    char c = S[i];
    if (is_vowel(c)) {
      dq.push_back(streak);
      streak = 0;
    } else ++streak;
  }
  dq.push_back(streak);

  if (dq.size() < 2) return cout << "-1\n", void();
  dq.pop_front(); dq.pop_back();

  ll ans = 1;
  for (int e : dq) ans = (ans * (e + 1)) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
