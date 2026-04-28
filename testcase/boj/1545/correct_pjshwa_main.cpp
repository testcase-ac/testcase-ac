#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  int t[26]{};
  for (char c : S) t[c - 'a']++;
  for (int i = 0; i < 26; i++) {
    if (t[i] > (N + 1) / 2) return cout << "-1\n", void();
  }

  int ans[N];
  for (int i = 0; i < (N + 1) / 2; i++) {
    int use;
    for (int c = 0; c < 26; c++) {
      if (t[c]) {
        ans[i] = c; t[c]--;
        break;
      }
    }
  }

  for (int i = (N + 1) / 2; i < N; i++) {
    int j = N - i - 1, use;
    for (int c = 0; c < 26; c++) {
      if (t[c] && c != ans[j]) {
        ans[i] = c; t[c]--;
        break;
      }
    }
  }

  for (int i = 0; i < N; i++) cout << char(ans[i] + 'a');
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
