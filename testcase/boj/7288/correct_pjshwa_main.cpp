#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  map<string, string> p2a, a2p;
  for (int i = 0; i < N; ++i) {
    string pre, area; cin >> pre >> area;
    p2a[pre] = area;
    a2p[area] = pre;
  }

  int R; cin >> R;
  vector<tuple<int, int, string, string>> B;
  for (int i = 0; i < R; ++i) {
    int yr, op; string area, ops; cin >> yr >> op >> area >> ops;
    B.emplace_back(yr, op, area, ops);
  }
  sort(B.begin(), B.end());

  vector<tuple<int, int, int, string>> Q;
  int ys, ye, Z = 0; string o;
  while (cin >> ys >> ye >> o) {
    if (ys == 0) break;
    Q.emplace_back(ys, ye, Z++, o);
  }
  sort(Q.begin(), Q.end());

  auto apply_area_change = [&](int i) {
    auto [yr, op, area, ops] = B[i];
    if (op == 3) {
      auto pre = a2p[area], newpre = ops;
      p2a[newpre] = area; p2a.erase(pre);
      a2p[area] = newpre;
    }
  };

  auto apply_local_change = [&](int i, string& local) {
    auto [yr, op, area, ops] = B[i];

    int idx = stoi(ops) - 1;
    if (op == 1) {
      char c = local[idx];
      local = local.substr(0, idx) + c + local.substr(idx);
    }
    if (op == 2) {
      swap(local[idx], local[idx + 1]);
    }
  };

  vector<string> ans(Z); int bi = 0;
  for (int qi = 0; qi < Z; ++qi) {
    auto [ys, ye, zi, o] = Q[qi];
    while (bi < R && get<0>(B[bi]) <= ys) {
      apply_area_change(bi);
      ++bi;
    }

    // Find area
    auto it = p2a.upper_bound(o);
    assert(it != p2a.begin());
    --it;

    string pre = it->first, area = it->second;
    string local = o.substr(pre.size());
    // cout << "area: " << area << ", local: " << local << "\n";

    for (int ci = bi; ci < R && get<0>(B[ci]) <= ye; ++ci) {
      auto [yr, op, barea, ops] = B[ci];
      if (area != barea) continue;
      if (op == 3) pre = ops;
      else apply_local_change(ci, local);
    }
    ans[zi] = pre + local;
  }

  for (auto& e : ans) cout << e << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
