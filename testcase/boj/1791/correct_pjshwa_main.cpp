#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
queue<int> order[MAXN], wait[MAXN + 1];

void solve() {
  int n, m; cin >> n >> m;

  int tot = 0; vector<pii> start_v;
  for (int i = 0; i < n; ++i) {
    int t, k; cin >> t >> k;
    start_v.emplace_back(t, i);

    tot += k;
    while (k--) {
      int x; cin >> x;
      order[i].push(x);
    }
  }
  sort(start_v.begin(), start_v.end(), greater<>());

  int ans = 0;
  queue<int> wave, nwave;
  vector<int> wave_int(m + 1);
  priority_queue<pii, vector<pii>, greater<pii>> sorter;

  for (int t = 0; tot; ++t) {
    while (!wave.empty()) {
      int j = wave.front(); wave.pop();
      ans = max(ans, t); --tot;

      int p = wait[j].front(); wait[j].pop();
      wave_int[j] = 0;
      if (!wait[j].empty()) nwave.push(j);

      if (order[p].empty()) continue;
      int o = order[p].front(); order[p].pop();
      sorter.emplace(p, o);
    }

    while (!start_v.empty() && start_v.back().first == t) {
      int p = start_v.back().second; start_v.pop_back();
      int o = order[p].front(); order[p].pop();
      sorter.emplace(p, o);
    }

    while (!sorter.empty()) {
      auto [p, q] = sorter.top(); sorter.pop();
      wait[q].push(p);
      if (wave_int[q] == 0) wave.push(q), wave_int[q] = 1;
    }

    while (!nwave.empty()) {
      int f = nwave.front(); nwave.pop();
      if (wave_int[f] == 1) continue;
      wave.push(f); wave_int[f] = 1;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
