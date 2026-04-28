#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool compare(vector<string>& a, vector<string>& b) {
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] != b[i]) return a[i] < b[i];
  }
  return false;
}

void solve() {
  vector<string> cows{"Bessie", "Buttercup", "Belinda", "Beatrice", "Bella", "Blue", "Betsy", "Sue"};
  int p[8];
  iota(p, p + 8, 0);

  int N;
  cin >> N;
  vector<pair<string, string>> ops;
  for (int i = 0; i < N; i++) {
    string op1, op2;
    cin >> op1;
    for (int j = 0; j < 5; j++) cin >> op2;
    ops.push_back({op1, op2});
  }

  vector<string> ans = cows;
  do {
    map<string, int> inv;
    for (int i = 0; i < 8; i++) inv[cows[i]] = p[i];

    bool valid = true;
    for (auto& [op1, op2] : ops) {
      if (abs(inv[op1] - inv[op2]) == 1) continue;
      valid = false;
    }
    if (!valid) continue;

    vector<string> cur(8);
    for (int i = 0; i < 8; i++) cur[p[i]] = cows[i];

    if (compare(cur, ans)) ans = cur;

  } while (next_permutation(p, p + 8));


  for (auto& e : ans) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
