#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

typedef vector<int> seq_t;

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
  int M, N; cin >> M >> N;

  vector<int> A(2 * N), D(2 * N - 1);
  for (int i = 0; i < N; ++i) cin >> A[i];
  if (N == 1) return cout << M << '\n', void();

  for (int i = N; i < 2 * N; ++i) A[i] = A[i - N] + M;
  for (int i = 1; i < 2 * N; ++i) {
    D[i - 1] = A[i] - A[i - 1];
  }
  D.pop_back();

  int z = kmp(D, vector<int>(D.begin(), D.begin() + N - 1)).size();
  assert(M % z == 0);
  cout << M / z << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
