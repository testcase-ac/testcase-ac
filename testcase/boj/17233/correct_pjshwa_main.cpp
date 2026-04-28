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

const int MAXN = 100, INF = 0x3f3f3f3f;
vector<int> occ[MAXN];

void solve() {
  int N; cin >> N;
  vector<pair<int, string>> patterns(N);
  for (int i = 0; i < N; ++i) cin >> patterns[i].first >> patterns[i].second;

  int L; string T; cin >> L >> T;
  for (int i = 0; i < N; ++i) occ[i] = kmp(T, patterns[i].second);

  int ans = L;
  for (int si = 0; si < L; ++si) {
    int ei = si;
    for (int i = 0; i < N; ++i) {
      int len = patterns[i].first;
      int sp_i = lower_bound(occ[i].begin(), occ[i].end(), si) - occ[i].begin();
      if (sp_i == (int)occ[i].size()) ei = INF;
      else {
        int sp = occ[i][sp_i];
        int ep = sp + len;
        ei = max(ei, ep);
      }
    }
    ans = min(ans, ei - si);
  }

  cout << ans << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
