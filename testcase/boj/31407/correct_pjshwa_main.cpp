#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, L; cin >> N >> L; L *= 4;
  vector<tii> mushs_o;
  for (int i = 1; i <= N; ++i) {
    int pos; string dir; cin >> pos >> dir;
    mushs_o.emplace_back(4 * pos + 1, dir == "L" ? -1 : 1, i);
  }

  vector<tii> Pos[L + 1], mushs;
  auto move_mushs = [&]() {
    for (int i = 0; i <= L; ++i) Pos[i].clear();
    for (auto& [pos, dir, idx] : mushs) {
      pos += dir;
      Pos[pos].emplace_back(pos, dir, idx);
    }
    for (int i = 0; i <= L; ++i) {
      if (Pos[i].size() <= 1) continue;
      for (auto& [pos, dir, idx] : Pos[i]) dir = -dir;
    }
    mushs.clear();
    for (int i = 1; i < L; ++i) {
      for (auto p : Pos[i]) mushs.emplace_back(p);
    }

    vector<int> popped_l, popped_r;
    for (auto& p : Pos[0]) popped_l.emplace_back(get<2>(p));
    for (auto& p : Pos[L]) popped_r.emplace_back(get<2>(p));
    return make_pair(popped_l, popped_r);
  };

  auto change_all_dirs = [&]() {
    for (auto& [pos, dir, idx] : mushs) dir = -dir;
  };

  int maxv = 0, maxk = -1;
  {
    mushs = mushs_o;
    while (!mushs.empty()) {
      auto [popped_l, popped_r] = move_mushs();
      maxv += popped_l.size();
    }
  }

  for (int k = 0; k <= N; ++k) {
    int sumv = 0; mushs = mushs_o;
    if (k == 0) change_all_dirs();

    while (!mushs.empty()) {
      auto [popped_l, popped_r] = move_mushs();
      sumv += popped_l.size();
      while (!popped_l.empty()) {
        int idx = popped_l.back(); popped_l.pop_back();
        if (idx == k) change_all_dirs();
      }
      while (!popped_r.empty()) {
        int idx = popped_r.back(); popped_r.pop_back();
        if (idx == k) change_all_dirs();
      }
    }
    if (sumv > maxv) {
      maxv = sumv;
      maxk = k;
    }
  }

  cout << maxv << '\n';
  if (maxk == -1) cout << "0\n";
  else cout << "1\n" << maxk << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
