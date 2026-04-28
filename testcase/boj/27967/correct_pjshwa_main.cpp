#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int N; string S, T;

bool is_valid() {
  int cnt = 0;
  for (char c : T) {
    if (c == '(') cnt++;
    else cnt--;
    if (cnt < 0) return false;
  }
  return cnt == 0;
}

void dfs(int i) {
  if (i == N) {
    if (is_valid()) {
      cout << T << '\n';
      exit(0);
    }
    return;
  }

  if (S[i] == 'G') {
    T[i] = '(';
    dfs(i + 1);
    T[i] = ')';
    dfs(i + 1);
  }
  else {
    T[i] = S[i];
    dfs(i + 1);
  }
}

void solve() {
  cin >> N >> S; T = S;
  dfs(0);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
