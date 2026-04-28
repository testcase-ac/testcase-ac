#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int sq_to_reach(int s, int e) {
  int res = 0;
  while (s < e) {
    s *= 2;
    res++;
  }
  return res;
}

void solve() {
  int src, dst; cin >> src >> dst;

  map<int, int> src_fs, dst_fs;
  for (int f = 2; f * f <= src; f++) while (src % f == 0) src_fs[f]++, src /= f;
  if (src > 1) src_fs[src]++;
  for (int f = 2; f * f <= dst; f++) while (dst % f == 0) dst_fs[f]++, dst /= f;
  if (dst > 1) dst_fs[dst]++;

  int sq_times = 0;
  for (auto& [dst_k, dst_v] : dst_fs) {
    if (!src_fs.count(dst_k)) return cout << "Impossible\n", void();
    sq_times = max(sq_times, sq_to_reach(src_fs[dst_k], dst_v));
  }

  // remove unnecessary factors in src_fs
  for (auto& [src_k, src_v] : src_fs) {
    if (dst_fs.count(src_k)) continue;
    for (int it = 0; it < src_v; it++) cout << src_k << ' ';
  }

  for (int it = 0; it < sq_times; it++) {
    for (auto& [dst_k, dst_v] : dst_fs) {
      int& src_v = src_fs[dst_k];

      // reduce occurence of dst_k in src_fs
      // as much as possible before squaring
      while (src_v > 1 && sq_to_reach(src_v - 1, dst_v) <= sq_times - it) {
        cout << dst_k << ' ';
        src_v--;
      }
    }

    cout << "0 ";
    for (auto& [dst_k, dst_v] : dst_fs) src_fs[dst_k] *= 2;
  }

  for (auto& [dst_k, dst_v] : dst_fs) {
    int& src_v = src_fs[dst_k];
    while (src_v > dst_v) {
      cout << dst_k << ' ';
      src_v--;
    }
  }
  cout << '\n';

  for (auto& [dst_k, dst_v] : dst_fs) {
    assert(src_fs[dst_k] == dst_v);
    // cout << "src_fs[" << dst_k << "] = " << src_fs[dst_k] << ", dst_v = " << dst_v << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
