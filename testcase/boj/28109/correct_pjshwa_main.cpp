#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N, K, cur; string S;
void dfs(int i) {
  for (char c = 'A'; c < S[i]; c++) {
    cur++;
    if (cur == K) {
      S[i] = c; cout << S << '\n';
      exit(0);
    }
  }

  if (i < N - 1) dfs(i + 1);
  else {
    cur++;
    if (cur == K) {
      cout << S << '\n';
      exit(0);
    }
  }

  for (char c = S[i] + 1; c <= 'Z'; c++) {
    cur++;
    if (cur == K) {
      S[i] = c; cout << S << '\n';
      exit(0);
    }
  }
}

void solve() {
  cin >> N >> K >> S;
  dfs(0);
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
