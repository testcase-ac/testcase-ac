#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<pll> haystack, needle, repl;
int n, m;
bool match(int i) {
  for (int l = 1; l < m - 1; l++) {
    if (haystack[i + l] != needle[l]) return false;
  }
  if (haystack[i].first != needle[0].first) return false;
  if (haystack[i].second < needle[0].second) return false;
  if (haystack[i + m - 1].first != needle[m - 1].first) return false;
  if (haystack[i + m - 1].second < needle[m - 1].second) return false;

  return true;
}

void solve() {
  string S; int T;
  while (1) {
    cin >> S;
    if (S == "$") break;

    cin >> T;
    haystack.emplace_back(S[0] - 'A', T);
  }
  while (1) {
    cin >> S;
    if (S == "$") break;

    cin >> T;
    needle.emplace_back(S[0] - 'A', T);
  }
  while (1) {
    cin >> S;
    if (S == "$") break;

    cin >> T;
    repl.emplace_back(S[0] - 'A', T);
  }

  n = haystack.size(), m = needle.size();
  for (int i = 0; i < n - m + 1; i++) {
    if (match(i)) {
      vector<pll> tmp, ans;
      for (int j = 0; j < i; j++) tmp.emplace_back(haystack[j]);
      if (m == 1) {
        for (auto& p : repl) tmp.emplace_back(p);
        if (haystack[i].second > needle[0].second) {
          tmp.emplace_back(haystack[i].first, haystack[i].second - needle[0].second);
        }
      }
      else {
        if (haystack[i].second > needle[0].second) {
          tmp.emplace_back(haystack[i].first, haystack[i].second - needle[0].second);
        }
        for (auto& p : repl) tmp.emplace_back(p);
        if (haystack[i + m - 1].second > needle[m - 1].second) {
          tmp.emplace_back(haystack[i + m - 1].first, haystack[i + m - 1].second - needle[m - 1].second);
        }
      }
      for (int j = i + m; j < n; j++) tmp.emplace_back(haystack[j]);

      int last = -1;
      for (auto& p : tmp) {
        if (last == p.first) {
          ans.back().second += p.second;
        }
        else {
          ans.emplace_back(p);
          last = p.first;
        }
      }

      for (auto& [k, v] : ans) cout << (char)(k + 'A') << ' ' << v << ' ';
      cout << "$\n";

      return;
    }
  }

  for (auto& [k, v] : haystack) cout << (char)(k + 'A') << ' ' << v << ' ';
  cout << "$\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
