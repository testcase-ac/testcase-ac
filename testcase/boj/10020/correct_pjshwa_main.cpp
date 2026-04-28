#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 500;
int D[MAX + 10];
int N;

bool match(vector<int>& d) {
  int mi, mv = -1;
  for (int i = 1; i <= N; i++) {
    if (d[i] > mv) {
      mv = d[i];
      mi = i;
    }
  }

  vector<pii> rest;
  for (int i = 1; i <= N; i++) {
    if (d[i] == 0 || i == mi) continue;
    rest.emplace_back(d[i], i);
  }
  sort(rest.begin(), rest.end());

  while (d[mi]) {
    if (rest.empty()) return false;

    int v = rest.back().second; rest.pop_back();
    d[mi]--, d[v]--;
  }

  return true;
}

bool check(int i) {
  vector<int> d{0};
  for (int j = 1; j <= N + 1; j++) {
    if (i != j) d.push_back(D[j]);
  }

  int it = N;
  while (it--) {
    if (!match(d)) return false;
  }
  return true;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N + 1; i++) cin >> D[i];

  vector<int> ans;
  for (int i = 1; i <= N + 1; i++) {
    if (check(i)) ans.push_back(i);
  }

  cout << ans.size() << '\n';
  for (int e : ans) cout << e << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
