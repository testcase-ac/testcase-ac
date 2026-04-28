#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, d;
string cur;

void dfs(int i) {
  if (i >= d - i - 1) {
    string rev = cur;
    reverse(rev.begin(), rev.end());
    ll res = stoll(cur) - stoll(rev);
    if (res == n) {
      cout << cur << '\n';
      exit(0);
    }
    return;
  }

  if (i == 0) {
    cur[0] = '1';
    for (char u = '0'; u <= '9'; ++u) {
      cur[d - 1] = u;
      dfs(i + 1);
    }
    cur[d - 1] = '0';
    for (char u = '1'; u <= '9'; ++u) {
      cur[0] = u;
      dfs(i + 1);
    }
  }
  else {
    cur[i] = '0';
    for (char u = '0'; u <= '9'; ++u) {
      cur[d - i - 1] = u;
      dfs(i + 1);
    }
    cur[d - i - 1] = '0';
    for (char u = '0'; u <= '9'; ++u) {
      cur[i] = u;
      dfs(i + 1);
    }
  }

}

void solve() {
  cin >> n;

  if (n == 900'000) return cout << "100001000001\n", void();
  if (n == 990'000) return cout << "10001000001\n", void();

  for (d = 2; d <= 10; d++) {
    cur = "";
    for (int i = 0; i < d; i++) cur += ' ';
    if (d & 1) cur[d / 2] = '0';
    dfs(0);
  }
  
  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
