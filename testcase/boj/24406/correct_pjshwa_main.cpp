#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MOD = 1e9 + 7;

bool is_vowel(char c) {
  return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U' ||
         c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

string S;
ll L[10][MAXN], R[10][MAXN], N;
vector<char> V = {'A', 'E', 'I', 'O', 'U', 'a', 'e', 'i', 'o', 'u'};
vector<char> C = {'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M',
                  'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Y', 'Z',
                  'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
                  'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};

int w_consonant(char c) {
  for (int ci = 0; ci < 10; ++ci) {
    int cnt_l = 0;
    for (int i = 0; i < N; ++i) {
      L[ci][i] = i == 0 ? 0 : L[ci][i - 1];

      if (S[i] == V[ci]) ++cnt_l;
      else if (S[i] == c) L[ci][i] = (L[ci][i] + cnt_l) % MOD;
    }

    int cnt_r = 0;
    for (int i = N - 1; i >= 0; --i) {
      R[ci][i] = i == N - 1 ? 0 : R[ci][i + 1];

      if (S[i] == V[ci]) ++cnt_r;
      else if (S[i] == c) R[ci][i] = (R[ci][i] + cnt_r) % MOD;
    }
  }

  ll ret = 0;
  for (int i = 0; i < N; ++i) {
    if (!is_vowel(S[i])) continue;

    for (int lci = 0; lci < 10; ++lci) for (int rci = 0; rci < 10; ++rci) {
      if (lci == rci) continue;

      char lc = V[lci], rc = V[rci];
      if (lc == S[i] || rc == S[i]) continue;

      ret = (ret + L[lci][i] * R[rci][i]) % MOD;
    }
  }

  return ret;
}

void solve() {
  cin >> S;
  N = S.size();

  for (int ci = 0; ci < 10; ++ci) {
    int cnt_l = 0;
    for (int i = 0; i < N; ++i) {
      L[ci][i] = i == 0 ? 0 : L[ci][i - 1];

      if (S[i] == V[ci]) ++cnt_l;
      else if (!is_vowel(S[i])) L[ci][i] = (L[ci][i] + cnt_l) % MOD;
    }

    int cnt_r = 0;
    for (int i = N - 1; i >= 0; --i) {
      R[ci][i] = i == N - 1 ? 0 : R[ci][i + 1];

      if (S[i] == V[ci]) ++cnt_r;
      else if (!is_vowel(S[i])) R[ci][i] = (R[ci][i] + cnt_r) % MOD;
    }
  }

  ll tot = 0;
  for (int i = 0; i < N; ++i) {
    if (!is_vowel(S[i])) continue;

    for (int lci = 0; lci < 10; ++lci) for (int rci = 0; rci < 10; ++rci) {
      if (lci == rci) continue;

      char lc = V[lci], rc = V[rci];
      if (lc == S[i] || rc == S[i]) continue;

      tot = (tot + L[lci][i] * R[rci][i]) % MOD;
    }
  }

  ll ans = tot;
  for (char c : C) ans = (ans - w_consonant(c) + MOD) % MOD;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
