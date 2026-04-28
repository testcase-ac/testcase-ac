#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
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

char v[(int)1e6 + 1];
int main() {
  fast_io();

  int n;
  cin >> n;

  char p;
  seq_t pattern, text;
  for (int i = 0; i < n; i++) cin >> v[i];
  for (int i = 0; i < n; i++) text.push_back(v[i]);
  for (int i = 0; i < n; i++) text.push_back(v[i]);
  for (int i = 0; i < n; i++) {
    cin >> p;
    pattern.push_back(p);
  }

  text.pop_back();

  int ans = kmp(text, pattern).size();
  int gcd_v = __gcd(ans, n);
  cout << ans / gcd_v << '/' << n / gcd_v << '\n';
}
