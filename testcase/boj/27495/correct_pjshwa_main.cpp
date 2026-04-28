#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 9;
string A[MAX][MAX];

int get_midx(int i, int j) {
  int ui = i / 3, uj = j / 3;
  int ret = 3 * ui + uj;
  if (ret >= 5) ret--;
  return ret;
}

bool is_mjob(int i, int j) {
  return i % 3 == 1 && j % 3 == 1;
}

bool is_msquare(int i, int j) {
  return 3 <= i && i <= 5 && 3 <= j && j <= 5;
}

void solve() {
  for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) cin >> A[i][j];

  vector<pair<string, int>> jobs_m;
  vector<string> jobs_s[8];
  for (int i = 0; i < 9; i++) for (int j = 0; j < 9; j++) {
    if (is_msquare(i, j)) continue;

    int idx = get_midx(i, j);
    if (is_mjob(i, j)) jobs_m.push_back({A[i][j], idx});
    else jobs_s[idx].push_back(A[i][j]);
  }

  sort(jobs_m.begin(), jobs_m.end());
  for (int i = 0; i < 8; i++) sort(jobs_s[i].begin(), jobs_s[i].end());

  for (int i = 0; i < 8; i++) {
    auto [job_m, idx] = jobs_m[i];
    cout << "#" << i + 1 << ". " << job_m << '\n';

    for (int j = 0; j < 8; j++) {
      cout << "#" << i + 1 << '-' << j + 1 << ". ";
      cout << jobs_s[idx][j] << '\n';
    }
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
