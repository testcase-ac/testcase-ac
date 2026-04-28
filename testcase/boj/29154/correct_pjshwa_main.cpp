#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void calculate_pi(vector<int>& pi, const vector<int>& str) {
  pi[0] = -1;
  for (int i = 1, j = -1; i < str.size(); i++) {
    while (j >= 0 && str[i] != str[j + 1]) j = pi[j];
    if (str[i] == str[j + 1])
      pi[i] = ++j;
    else
      pi[i] = -1;
  }
}

vector<int> kmp(const vector<int>& text, const vector<int>& pattern) {
  vector<int> pi(pattern.size()), ans;
  if (pattern.size() == 0) return ans;
  calculate_pi(pi, pattern);

  for (int i = 0, j = -1; i < text.size(); i++) {
    while (j >= 0 && text[i] != pattern[j + 1]) j = pi[j];
    if (text[i] == pattern[j + 1]) {
      j++;
      ans.push_back(i);
      if (j + 1 == pattern.size()) j = pi[j];
    }
  }

  return ans;
}

void solve() {
  int N, M; cin >> N >> M;

  vector<int> text(N), pattern(M);
  for (int i = 0; i < N; ++i) cin >> text[i];
  for (int i = 0; i < M; ++i) cin >> pattern[i];
  reverse(text.begin(), text.end());
  reverse(pattern.begin(), pattern.end());

  vector<int> matches = kmp(text, pattern);

  int U[N]; memset(U, 0, sizeof U);
  for (int match : matches) U[match] = 1;

  vector<int> streaks;
  int cur_streak = 0;
  for (int i = 0; i < N; ++i) {
    if (U[i] > 0) {
      ++cur_streak;
    }
    else {
      if (cur_streak > 0) {
        streaks.push_back(cur_streak);
        cur_streak = 0;
      }
    }
  }
  if (cur_streak > 0) {
    streaks.push_back(cur_streak);
  }

  int total_xor = 0;
  for (int streak : streaks) {
    total_xor ^= streak;
  }

  if (total_xor == 0) cout << "Second\n";
  else cout << "First\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
