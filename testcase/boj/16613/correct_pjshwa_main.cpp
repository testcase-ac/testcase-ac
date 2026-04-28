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

bool is_match(char t, char p) {
  return t == p || t == '_';
}

// returns longest prefix of S that matches pattern subsequence
int max_prefix_match(const string& S, const string& pattern) {
  string combined = pattern + "#" + S;
  vector<int> pi(combined.size());
  calculate_pi(pi, combined);
  int best = 0;
  for (int i = pattern.size() + 1; i < pi.size(); i++) {
    best = max(best, pi[i] + 1);
  }
  return best;
}

void solve() {
  string S, T = "_"; cin >> S;
  string S_even, S_odd;
  for (int i = 0; i < S.size(); i++) {
    if (i % 2 == 0) S_even += S[i];
    else S_odd += S[i];
  }

  int n_even = max_prefix_match(S, S_even);
  int n_odd  = max_prefix_match(S, S_odd);

  int ans = max(2 * n_even, 2 * n_odd + 1);
  cout << "Result: " << ans << endl;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
