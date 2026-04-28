#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const char k1[] = "QWERTYUIOP";
const char k2[] = "ASDFGHJKL";
const char k3[] = "ZXCVBNM";
const int INF = 1e9 + 7;

int cost[26][26];

void solve() {
  string s;
  cin >> s;
  int n = s.size();

  int ans = 0;
  for (int i = 0; i < n - 1; i++) {
    ans += cost[s[i] - 'A'][s[i + 1] - 'A'];
  }
  cout << ans * 2 + n << '\n';
}

int main() {
  fast_io();

  for (int i = 0; i < 26; i++) for (int j = 0; j < 26; j++) {
    if (i != j) cost[i][j] = INF;
  }

  int k1sz = strlen(k1), k2sz = strlen(k2), k3sz = strlen(k3);
  for (int i = 0; i < k1sz - 1; i++) {
    cost[k1[i] - 'A'][k1[i + 1] - 'A'] = 1;
    cost[k1[i + 1] - 'A'][k1[i] - 'A'] = 1;
  }
  for (int i = 0; i < k2sz - 1; i++) {
    cost[k2[i] - 'A'][k2[i + 1] - 'A'] = 1;
    cost[k2[i + 1] - 'A'][k2[i] - 'A'] = 1;
  }
  for (int i = 0; i < k3sz - 1; i++) {
    cost[k3[i] - 'A'][k3[i + 1] - 'A'] = 1;
    cost[k3[i + 1] - 'A'][k3[i] - 'A'] = 1;
  }
  for (int i = 0; i < k2sz; i++) {
    cost[k2[i] - 'A'][k1[i] - 'A'] = cost[k1[i] - 'A'][k2[i] - 'A'] = 1;
    cost[k2[i] - 'A'][k1[i + 1] - 'A'] = cost[k1[i + 1] - 'A'][k2[i] - 'A'] = 1;

    if (i < 7) cost[k2[i] - 'A'][k3[i] - 'A'] = cost[k3[i] - 'A'][k2[i] - 'A'] = 1;
    if (0 < i && i < 8) cost[k2[i] - 'A'][k3[i - 1] - 'A'] = cost[k3[i - 1] - 'A'][k2[i] - 'A'] = 1;
  }

  // Floyd-warshall
  for (int k = 0; k < 26; k++) {
    for (int i = 0; i < 26; i++) {
      for (int j = 0; j < 26; j++) cost[i][j] = min(cost[i][k] + cost[k][j], cost[i][j]);
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
