#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<tuple<int, string, int>> submissions;

  for (int i = 0; i < n; i++) {
    int id, res, x;
    string user;
    cin >> id >> user >> res >> x >> x >> x >> x;
    if (user == "megalusion") continue;

    submissions.emplace_back(id, user, res == 4);
  }
  sort(submissions.begin(), submissions.end());

  unordered_map<string, pair<int, int>> u;
  for (auto [i, s, r] : submissions) {
    if (!u.count(s)) u[s] = {0, 0};
    if (u[s].first == 1) continue;

    if (r) u[s].first = 1;
    else u[s].second++;
  }

  int rc = 0, wc = 0;
  for (auto [s, p] : u) {
    if (!p.first) continue;
    rc += p.first;
    wc += p.second;
  }

  if (rc + wc == 0) cout << "0\n";
  else cout << fixed << setprecision(10) << 100.0 * rc / (rc + wc) << '\n';
}
