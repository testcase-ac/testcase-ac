#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

typedef string seq_t;

void calculate_pi(vector<int>& pi, const seq_t& str) {
  pi[0] = -1;
  for (int i = 1, j = -1; i < str.size(); i++) {
    while (j >= 0 && str[i] != str[j + 1]) j = pi[j];
    if (str[i] == str[j + 1])
      pi[i] = ++j;
    else
      pi[i] = -1;
  }
}

// returns all positions matched
// O(|text|+|pattern|)
vector<int> kmp(const seq_t& text, const seq_t& pattern) {
  vector<int> pi(pattern.size()), ans;
  if (pattern.size() == 0) return ans;
  calculate_pi(pi, pattern);
  for (int i = 0, j = -1; i < text.size(); i++) {
    while (j >= 0 && text[i] != pattern[j + 1]) j = pi[j];
    if (text[i] == pattern[j + 1]) {
      j++;
      if (j + 1 == pattern.size()) {
        ans.push_back(i - j);
        j = pi[j];
      }
    }
  }
  return ans;
}

void solve() {
  string A, B; cin >> A >> B;
  B += B; B.pop_back();
  cout << kmp(B, A).size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
