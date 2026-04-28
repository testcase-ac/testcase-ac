#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, L; cin >> N >> L;
  vector<int> P(N), D(N);
  for (int i = 0; i < N; ++i) cin >> P[i] >> D[i];

  vector<pii> poss;
  for (int i = 0; i < N; ++i) poss.emplace_back(P[i], i);
  sort(poss.begin(), poss.end());

  deque<int> idxs;
  for (int i = 0; i < N; ++i) idxs.push_back(poss[i].second + 1);

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < N; ++i) {
    if (D[i] == 0) pq.emplace(P[i], 0);
    else pq.emplace(L - P[i], 1);
  }

  vector<pii> ord;
  while (!pq.empty()) {
    auto [pos, dir] = pq.top(); pq.pop();
    if (dir) {
      ord.emplace_back(pos, idxs.back());
      idxs.pop_back();
    } else {
      ord.emplace_back(pos, idxs.front());
      idxs.pop_front();
    }
  }
  sort(ord.begin(), ord.end());

  for (auto [pos, idx] : ord) cout << idx << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
