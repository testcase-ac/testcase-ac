#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e4;
bool vis[MAX + 1];

bool is_power_of_two(int x) {
  return (x & (x - 1)) == 0;
}

void solve() {
  int N; cin >> N;

  vector<int> ans; int pw = N + 1;
  while (!is_power_of_two(pw)) pw++;

  for (int i = N; i >= 1; i--) {
    int r = pw - i;
    while (r > N || vis[r]) pw /= 2, r = pw - i;
    ans.push_back(r); vis[r] = true;
  }
  reverse(ans.begin(), ans.end());
  for (int e : ans) cout << e << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
