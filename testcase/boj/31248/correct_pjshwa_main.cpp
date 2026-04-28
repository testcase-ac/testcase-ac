#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<pair<int, int>> traj;
int N, D = 3;

void move_l(int s, int e, int l) {
  int v;
  for (v = 0; v < 3; ++v) {
    if (v != s && v != e) break;
  }

  if (l == 1) traj.emplace_back(s, e);
  else {
    move_l(s, v, l - 1);
    traj.emplace_back(s, e);
    move_l(v, e, l - 1);
  }

}

void move_b(int s, int l) {
  int e1 = (s + 1) % 3, e2 = (s + 2) % 3;

  if (l == 1) {
    traj.emplace_back(s, D);
  }
  else if (l == 2) {
    traj.emplace_back(s, e1);
    traj.emplace_back(s, D);
    traj.emplace_back(e1, D);
  }
  else {
    move_l(s, e1, l - 2);
    traj.emplace_back(s, e2);
    traj.emplace_back(s, D);
    traj.emplace_back(e2, D);
    move_b(e1, l - 2);
  }
}

void solve() {
  cin >> N;
  move_b(0, N);

  cout << traj.size() << '\n';
  for (auto& [s, e] : traj) cout << (char)(s + 'A') << ' ' << (char)(e + 'A') << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
