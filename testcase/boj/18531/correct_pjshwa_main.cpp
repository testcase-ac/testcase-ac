#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void calculate_pi(vector<int>& pi, const string& str) {
  pi[0] = -1;
  for (int i = 1, j = -1; i < str.size(); i++) {
    while (j >= 0 && str[i] != str[j + 1]) j = pi[j];
    if (str[i] == str[j + 1])
      pi[i] = ++j;
    else
      pi[i] = -1;
  }
}

vector<int> kmp(const string& text, const string& pattern) {
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

const int INF = 0x3f3f3f3f;

void solve() {
  string A, B, C; cin >> A >> B >> C;
  int N = A.size();

  vector<int> start_B;
  for (int j = 0; j < N; ++j) {
    bool ok = true;
    for (int i = 0; i < N; ++i) ok &= A[i] != B[(i + j) % N];
    if (ok) start_B.push_back(j);
  }

  C += C; int ans = INF;
  vector<int> matches;

  for (int j : start_B) {
    string U = "";
    for (int i = 0; i < N; ++i) {
      int ai = A[i] - 'A' + 1, bi = B[(i + j) % N] - 'A' + 1;
      U += (char)((ai ^ bi) + 'A' - 1);
    }
    // cout << "j = " << j << ", U = " << U << '\n';

    matches = kmp(C, U);
    for (int cm : matches) {
      for (int bi : {j, -(N - j)}) for (int ci : {cm, -(N - cm)}) {
        // cout << "bi = " << bi << ", ci = " << ci << '\n';
        if (bi >= 0) {
          if (ci >= 0) ans = min(ans, max(bi, ci));
          else ans = min(ans, bi - ci);
        }
        else {
          if (ci >= 0) ans = min(ans, -bi + ci);
          else ans = min(ans, max(-bi, -ci));
        }
      }
    }
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
