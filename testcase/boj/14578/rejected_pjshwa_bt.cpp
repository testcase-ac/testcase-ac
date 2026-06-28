#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10, MOD = 1e9 + 7;
bool rred[MAX], cred[MAX];
bool rblue[MAX], cblue[MAX];
int n, ans;

void dfs(int i, int j) {
  if (i == n && j == 0) {
    bool able = true;
    for (int i = 0; i < n; i++) if (!rred[i] || !cred[i]) {
      able = false;
      break;
    }
    for (int i = 0; i < n; i++) if (!rblue[i] || !cblue[i]) {
      able = false;
      break;
    }
    if (able) ans++;
    return;
  }

  if (!rred[i] && !cred[j]) {
    rred[i] = cred[j] = 1;
    j == n - 1 ? dfs(i + 1, 0) : dfs(i, j + 1);
    rred[i] = cred[j] = 0;
  }

  if (!rblue[i] && !cblue[j]) {
    rblue[i] = cblue[j] = 1;
    j == n - 1 ? dfs(i + 1, 0) : dfs(i, j + 1);
    rblue[i] = cblue[j] = 0;
  }

  j == n - 1 ? dfs(i + 1, 0) : dfs(i, j + 1);
}

void solve() {
  cin >> n;
  dfs(0, 0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
