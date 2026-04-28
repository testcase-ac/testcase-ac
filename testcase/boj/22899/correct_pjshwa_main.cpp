#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
multiset<pair<int, int>> counts;
priority_queue<int> authors[MAX];

void print_counts() {
  multiset<pair<int, int>>::iterator it;
  for (it = counts.begin(); it != counts.end(); ++it) {
    cout << it->first << " " << it->second << endl;
  }
}
 
int main() {
  fast_io();

  int n, k;
  cin >> n >> k;

  vector<pair<int, int>> problems(n);
  for (int i = 0; i < n; i++) cin >> problems[i].second, problems[i].second--;
  for (int i = 0; i < n; i++) cin >> problems[i].first;
  sort(problems.begin(), problems.end());

  ll overall_difficulty = 0;
  for (int i = 0; i < k; i++) {
    auto [lev, auth] = problems[i];
    authors[auth].push(lev);
    overall_difficulty += lev;
  }
  for (int i = 0; i < n; i++) if (authors[i].size()) counts.insert({authors[i].size(), i});

  vector<ll> ans(n, -1);
  int pt = k, ccount = k;
  for (int l = n; l >= 1; l--) {
    auto start = counts.lower_bound({l + 1, -1});
    auto ostart = start;
    vector<pair<int, int>> new_els;
    int defi = 0;
    for (start; start != counts.end(); start++) {
      auto [lev, auth] = *start;
      for (int it = 0; it < lev - l; it++) {
        overall_difficulty -= authors[auth].top();
        authors[auth].pop();
        ccount--;
        defi++;
      }
      new_els.push_back({l, auth});
    }
    counts.erase(ostart, counts.end());
    for (auto el : new_els) counts.insert(el);

    while (defi--) {
      while (pt < n && authors[problems[pt].second].size() >= l) pt++;
      if (pt == n) break;

      if (authors[problems[pt].second].size()) {
        counts.erase(counts.lower_bound({authors[problems[pt].second].size(), problems[pt].second}));
      }
      overall_difficulty += problems[pt].first;
      authors[problems[pt].second].push(problems[pt].first);
      counts.insert({authors[problems[pt].second].size(), problems[pt].second});
      ccount++;
      pt++;
    }

    if (ccount < k) break;
    ans[l - 1] = overall_difficulty;
  }

  for (int i = 0; i < n; i++) cout << ans[i] << ' ';
}
