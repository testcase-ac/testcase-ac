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

const int MAX = 1000;
vector<int> A[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) {
    int Ki, zl; cin >> Ki >> zl;
    for (int j = 1; j < Ki; j++) {
      int z; cin >> z;
      A[i].push_back(z - zl);
      zl = z;
    }
  }

  int L, zl; cin >> L >> zl;
  vector<int> B;
  for (int i = 1; i < L; i++) {
    int z; cin >> z;
    B.push_back(z - zl);
    zl = z;
  }

  vector<int> ans;
  for (int i = 0; i < N; i++) {
    auto v = kmp(A[i], B);
    if (v.size() > 0) ans.push_back(i + 1);
  }

  if (ans.empty()) cout << -1;
  else for (int e : ans) cout << e << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
