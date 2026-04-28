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
      if (j + 1 == pattern.size()) {
        ans.push_back(i - j);
        j = pi[j];
      }
    }
  }
  return ans;
}

const int MAXV = 360000;

void solve() {
  int N; cin >> N;
  vector<int> A(MAXV * 2), B(MAXV);
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    A[x] = A[x + MAXV] = 1;
  }
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    B[x] = 1;
  }
  cout << (kmp(A, B).empty() ? "impossible" : "possible") << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
