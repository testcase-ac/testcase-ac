#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, C[6];
  cin >> N >> C[0] >> C[1] >> C[2] >> C[3] >> C[4] >> C[5];

  int mv = 0, mi;
  for (int i = 0; i < 6; i++) {
    if (2 * C[i] > N) return cout << "IMPOSSIBLE\n", void();
    if (C[i] > mv) mv = C[i], mi = i;
  }

  vector<int> r;
  for (int i : {0, 2, 4}) if (i != mi) r.push_back(i);

  vector<char> ans;
  for (int i = 0; i < C[mi]; i++) {
    ans.push_back("R Y B"[mi]);
    int j = 1;
    if (C[r[0]] > C[r[1]]) j = 0;
    ans.push_back("R Y B"[r[j]]);
    C[r[j]]--;
  }

  int it = C[r[0]] + C[r[1]];
  while (it--) {
    char b = ans.back();
    for (int i = 0; i < 2; i++) {
      int j = r[i];
      if (b == "R Y B"[j]) continue;
      ans.push_back("R Y B"[j]);
    }
  }

  for (char c : ans) cout << c; cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
