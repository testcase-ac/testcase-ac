#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size(), C[26]{};
  vector<deque<int>> P(26);
  for (int i = 0; i < N; ++i) {
    int ci = S[i] - 'a';
    ++C[ci]; P[ci].push_back(i);
  }

  int odd = 0, oddc;
  for (int c = 0; c < 26; ++c) {
    if (C[c] % 2) ++odd, oddc = c;
  }
  if (odd > 1) return cout << "NO\n", void();
  if (odd == 1) {
    stack<int> T; int Z = P[oddc].size();
    for (int i = 0; i < Z / 2; ++i) {
      T.push(P[oddc].front()); P[oddc].pop_front();
    }
    int oddi = P[oddc].front(); P[oddc].pop_front();
    if (abs(oddi - N / 2) > 1) return cout << "NO\n", void();
    for (int i = 0; i < Z / 2; ++i) {
      P[oddc].push_front(T.top()); T.pop();
    }
  }

  vector<int> V(N);
  for (int c = 0; c < 26; ++c) {
    if (P[c].empty()) continue;
    if (P[c].size() % 2) return cout << "NO\n", void();

    while (!P[c].empty()) {
      int f = P[c].front(), b = P[c].back();
      P[c].pop_front(); P[c].pop_back();

      int fdis = f, bdis = N - 1 - b;
      int ddis = abs(fdis - bdis);
      if (ddis > 2) return cout << "NO\n", void();
      if (ddis == 2) {
        if (fdis < bdis) ++V[f + 1], ++V[b - 1];
        else ++V[f - 1], ++V[b + 1];
      }
    }
  }

  for (int i = 0; i < N; ++i) if (V[i] > 1) return cout << "NO\n", void();
  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
