#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
int d[MAX + 1], res[MAX + 1][MAX + 1];
int N;

bool match() {
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
    res[mi][v] = res[v][mi] = 1;
    d[mi]--, d[v]--;
  }

  return true;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> d[i];

  int it = N;
  while (it--) {
    if (!match()) return cout << "-1\n", void();
  }

  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      cout << res[i][j] << ' ';
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
