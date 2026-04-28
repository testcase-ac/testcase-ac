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
  string S, T; cin >> S >> T;

  vector<string> Ts{T};
  for (int t = 0;; ++t) {
    if (Ts.empty()) return cout << "-1\n", void();

    for (auto& T : Ts) {
      if (!kmp(S, T).empty()) return cout << t << '\n', void();
    }

    vector<string> nTs;
    for (auto& T : Ts) {
      int bi = -1, Z = T.size(), ok = 1;
      for (int i = 0; i < Z; ++i) {
        if (T[i] == 'a') continue;
        if (bi == -1 || (i - bi) % 2 == 0) bi = i;
        else ok = 0;
      }
      if (!ok) continue;

      string nT = ""; int i = 0;
      if (bi % 2 == 0) nT += T[i++];

      while (i < Z) {
        assert(T[i] == 'a');
        if (i == Z - 1) {
          nT += '?'; ++i;
        } else {
          if (T[i + 1] == 'a') nT += 'a';
          else nT += 'b';
          i += 2;
        }
      }

      // cout << "T = " << T << " -> " << nT << '\n';
      if (nT.back() == '?') {
        nT.pop_back();
        string nTa = nT + 'a', nTb = nT + 'b';
        if (T != nTa) nTs.push_back(nTa);
        if (T != nTb) nTs.push_back(nTb);
      } else {
        if (T != nT) nTs.push_back(nT);
      }
    }

    Ts = nTs;
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
