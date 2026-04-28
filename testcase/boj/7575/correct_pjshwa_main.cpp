#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

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

// returns all positions matched
// O(|text|+|pattern|)
vector<int> kmp(const vector<int>& text, const vector<int>& pattern) {
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

const int MAXK = 100;
vector<int> B[MAXK];

void solve() {
  int K, N; cin >> K >> N; --K;

  int M; cin >> M;
  vector<int> A(M);
  for (int i = 0; i < M; ++i) cin >> A[i];

  for (int it = 0; it < K; ++it) {
    int L; cin >> L;
    B[it].resize(L);
    for (int i = 0; i < L; ++i) cin >> B[it][i];
  }

  for (int i = 0; i < M; ++i) {
    vector<int> pattern, pattern_rev;
    for (int j = 0; j < N && i + j < M; ++j) pattern.push_back(A[i + j]);
    if ((int)pattern.size() < N) break;
    pattern_rev = pattern;
    reverse(pattern_rev.begin(), pattern_rev.end());

    int ok = 1;
    for (int it = 0; it < K; ++it) {
      if (kmp(B[it], pattern).empty() && kmp(B[it], pattern_rev).empty()) {
        ok = 0;
        break;
      }
    }
    if (ok) return cout << "YES\n", void();
  }

  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
