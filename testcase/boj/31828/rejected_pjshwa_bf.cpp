#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 6;
string cur(MAXN, 'A');
int ans = 0;

void dfs(int i) {
  if (i == MAXN) {
    // check if cur contains 'MRDR' as subsequence
    int j = 0;
    for (char c : cur) {
      if (c == "MRDR"[j]) {
        if (++j == 4) {
          ++ans;
          break;
        }
      }
    }

    return;
  }

  for (char c = 'A'; c <= 'Z'; ++c) {
    cur[i] = c;
    dfs(i + 1);
  }


}

void solve() {
  dfs(0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
