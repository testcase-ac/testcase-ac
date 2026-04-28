#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

int main() {
  fast_io();

  int n, k;
  string s;
  cin >> n >> k >> s;

  set<int> js, os, is;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'J') js.insert(i);
    if (s[i] == 'O') os.insert(i);
    if (s[i] == 'I') is.insert(i);
  }

  if (js.size() < k || os.size() < k || is.size() < k) return cout << "-1\n", 0;

  int ans = INF;
  auto jsp = js.begin(), jep = js.begin(), osp = os.begin(), oep = os.begin(),
       isp = is.begin(), iep = is.begin();
  for (int i = 0; i < k - 1; i++) jep++, oep++, iep++;
  while (jep != js.end()) {
    bool able = true;
    while (*osp < *jep) {
      osp++, oep++;
      if (oep == os.end()) {
        able = false;
        break;
      }
    }
    if (!able) break;
    while (*isp < *oep) {
      isp++, iep++;
      if (iep == is.end()) {
        able = false;
        break;
      }
    }
    if (!able) break;

    ans = min(ans, *iep - *jsp - 3 * k + 1);
    jsp++, jep++;
  }

  cout << (ans == INF ? -1 : ans) << '\n';
}
